#include "air105_sensor.h"

#define SENSOR_UNLOCK_MAGIC      ((uint32_t)0x00000055)

uint32_t SENSOR_SetRand(uint32_t Rand)
{
    SENSOR->SEN_RNG_INI = Rand;
    return SENSOR->SEN_RNG_INI;
}

uint32_t SENSOR_EXTInit(SENSOR_EXTInitTypeDef *SENSOR_EXTInitStruct)
{
    if (SENSOR_EXTInitStruct == NULL)
        return 1;

    SENSOR->SEN_ANA0 |= 0x80000000;

    SENSOR->SEN_EXT_TYPE  = SENSOR_EXTInitStruct->SENSOR_Port_Pull
                          | SENSOR_EXTInitStruct->SENSOR_Port_Static
                          | SENSOR_EXTInitStruct->SENSOR_Port_Dynamic;

    SENSOR->SEN_EXT_CFG   = SENSOR_EXTInitStruct->SENSOR_DynamicFrequency
                          | (SENSOR_EXTInitStruct->SENSOR_Dynamic_Sample << 8)
                          | (SENSOR_EXTInitStruct->SENSOR_Static_Sample << 12);

    SENSOR->SEN_SOFT_EN   = SENSOR_EXTInitStruct->SENSOR_GlitchEnable
                          | (SENSOR_EXTInitStruct->SENSOR_PUPU_Enable << 1)
                          | (SENSOR_EXTInitStruct->SENSOR_Trig_Hold_Enable << 2);

    SENSOR->SEN_VG_DETECT = SENSOR_EXTInitStruct->SENSOR_PUPU_Frequency
                          | (SENSOR_EXTInitStruct->SENSOR_PUPU_DetectTime << 4)
                          | (SENSOR_EXTInitStruct->SENSOR_PUPU_HoldTime << 8);

    return 0;
}

uint32_t SENSOR_EXTPortCmd(uint32_t SENSOR_Port, FunctionalState NewState)
{
    uint32_t i;

    for (i = 0; i < 8; i++) {
        if (SENSOR_Port & (1U << i)) {
            if (NewState == ENABLE)
                SENSOR->SEN_EN[i] = ~SENSOR_UNLOCK_MAGIC;
            else
                SENSOR->SEN_EN[i] = SENSOR_UNLOCK_MAGIC;
        }
    }
    return 0;
}

uint32_t SENSOR_EXTCmd(FunctionalState NewState)
{
    uint32_t i;

    for (i = 0; i < 8; i++)
        SENSOR_EXTPortCmd(1U << i, NewState);

    return 0;
}

FlagStatus SENSOR_EXTIsRuning(void)
{
    uint32_t i;

    for (i = 0; i < 8; i++) {
        if (SENSOR->SEN_EN[i] != SENSOR_UNLOCK_MAGIC)
            return SET;
    }
    return RESET;
}

uint32_t SENSOR_ANACmd(uint32_t SENSOR_ANA, FunctionalState NewState)
{
    uint32_t idx;
    uint32_t bit;

    for (idx = 9; idx < 19; idx++) {
        bit = 1U << (idx - 9);
        if (SENSOR_ANA & bit) {
            if (NewState == ENABLE)
                SENSOR->SEN_EN[idx] = ~SENSOR_UNLOCK_MAGIC;
            else
                SENSOR->SEN_EN[idx] = SENSOR_UNLOCK_MAGIC;
        }
    }
    return 0;
}

void SENSOR_Lock(uint32_t SENSOR_LOCK)
{
    SENSOR->SEN_LOCK |= (SENSOR_LOCK & 0xFF);
}

void SENSOR_AttackRespMode(SENSOR_RespModeTypeDef SENSOR_RespMode)
{
    if (SENSOR_RespMode == SENSOR_CPUReset)
        SENSOR->SEN_ANA0 &= ~(1U << 31);
    else
        SENSOR->SEN_ANA0 |= (1U << 31);
}

int32_t SENSOR_GetITStatus(uint32_t ITState)
{
    return (SENSOR->SEN_STATE & ITState) ? SET : RESET;
}

int32_t SENSOR_GetITStatusReg(void)
{
    return SENSOR->SEN_STATE;
}

void SENSOR_ClearITPendingBit(void)
{
    SENSOR->SEN_ATTCLR = 0xFFFFFFFF;
}

FunctionalState SENSOR_GetEXTTrigPull(void)
{
    return (SENSOR->SEN_ANA1 & 0x01) ? ENABLE : DISABLE;
}

FunctionalState SENSOR_SetEXTTrigPull(FunctionalState NewState)
{
    if (NewState == ENABLE)
        SENSOR->SEN_ANA1 |= 0x01;
    else
        SENSOR->SEN_ANA1 &= ~0x01;
    return NewState;
}

FunctionalState SENSOR_GetEXTFilter(void)
{
    return (SENSOR->SEN_ANA1 & 0x02) ? ENABLE : DISABLE;
}

FunctionalState SENSOR_SetEXTFilter(FunctionalState NewState)
{
    if (NewState == ENABLE)
        SENSOR->SEN_ANA1 |= 0x02;
    else
        SENSOR->SEN_ANA1 &= ~0x02;
    return NewState;
}

uint32_t SENSOR_GetEXTPulsePeriod(void)
{
    return SENSOR->SEN_VG_DETECT & 0x01;
}

uint32_t SENSOR_SetEXTPulsePeriod(uint32_t u32Period)
{
    SENSOR->SEN_VG_DETECT = (SENSOR->SEN_VG_DETECT & ~0x01) | (u32Period & 0x01);
    return u32Period;
}

uint32_t SENSOR_GetEXTPulseHold(void)
{
    return (SENSOR->SEN_VG_DETECT >> 8) & 0x03;
}

uint32_t SENSOR_SetEXTPulseHold(uint32_t u32Hold)
{
    SENSOR->SEN_VG_DETECT = (SENSOR->SEN_VG_DETECT & ~(0x03 << 8)) | ((u32Hold & 0x03) << 8);
    return u32Hold;
}

FunctionalState SENSOR_GetEXTPulsePull(void)
{
    return (SENSOR->SEN_VG_DETECT & (1U << 16)) ? ENABLE : DISABLE;
}

FunctionalState SENSOR_SetEXTPulsePull(FunctionalState NewState)
{
    if (NewState == ENABLE)
        SENSOR->SEN_VG_DETECT |= (1U << 16);
    else
        SENSOR->SEN_VG_DETECT &= ~(1U << 16);
    return NewState;
}

uint32_t SENSOR_GetEXTStaticSample(void)
{
    return (SENSOR->SEN_EXT_CFG >> 12) & 0x03;
}

uint32_t SENSOR_SetEXTStaticSample(uint32_t u32Count)
{
    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~(0x03 << 12)) | ((u32Count & 0x03) << 12);
    return u32Count;
}

uint32_t SENSOR_GetEXTDynamicSample(void)
{
    return (SENSOR->SEN_EXT_CFG >> 8) & 0x03;
}

uint32_t SENSOR_SetEXTDynamicSample(uint32_t u32Count)
{
    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~(0x03 << 8)) | ((u32Count & 0x03) << 8);
    return u32Count;
}

uint32_t SENSOR_GetEXTDynamicFreq(void)
{
    return SENSOR->SEN_EXT_CFG & 0x03;
}

uint32_t SENSOR_SetEXTDynamicFreq(uint32_t u32Freq)
{
    SENSOR->SEN_EXT_CFG = (SENSOR->SEN_EXT_CFG & ~0x03) | (u32Freq & 0x03);
    return u32Freq;
}
