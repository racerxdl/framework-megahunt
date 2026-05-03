#include "air105_bpk.h"

#define BPK_LR_LOCK_SELF        ((uint32_t)0x00000001)
#define BPK_LR_LOCK_RESET       ((uint32_t)0x00000002)
#define BPK_LR_LOCK_KEYWRITE    ((uint32_t)0x00000004)
#define BPK_LR_LOCK_KEYREAD     ((uint32_t)0x00000008)
#define BPK_LR_LOCK_KEYCLEAR    ((uint32_t)0x00000010)
#define BPK_LR_LOCK_SCRAMBER    ((uint32_t)0x00000020)
#define BPK_LR_LOCK_ALL         (BPK_LR_LOCK_SELF | BPK_LR_LOCK_RESET | \
                                 BPK_LR_LOCK_KEYWRITE | BPK_LR_LOCK_KEYREAD | \
                                 BPK_LR_LOCK_KEYCLEAR | BPK_LR_LOCK_SCRAMBER)

FlagStatus BPK_IsReady(void)
{
    return (BPK->BPK_RDY & 0x01) ? SET : RESET;
}

ErrorStatus BPK_WriteKey(uint32_t *Key, uint32_t Key_Len, uint32_t Key_Offset)
{
    uint32_t i;

    if (Key == NULL || Key_Len == 0 || Key_Offset >= BPK_KEY_NUM)
        return ERROR;
    if (Key_Offset + Key_Len > BPK_KEY_NUM)
        return ERROR;
    if (BPK_IsReady() != SET)
        return ERROR;

    for (i = 0; i < Key_Len; i++)
        BPK->KEY[Key_Offset + i] = Key[i];

    return SUCCESS;
}

ErrorStatus BPK_ReadKey(uint32_t *Key, uint32_t Key_Len, uint32_t Key_Offset)
{
    uint32_t i;

    if (Key == NULL || Key_Len == 0 || Key_Offset >= BPK_KEY_NUM)
        return ERROR;
    if (Key_Offset + Key_Len > BPK_KEY_NUM)
        return ERROR;
    if (BPK_IsReady() != SET)
        return ERROR;

    for (i = 0; i < Key_Len; i++)
        Key[i] = BPK->KEY[Key_Offset + i];

    return SUCCESS;
}

void BPK_KeyWriteLock(uint16_t BPK_KEY_Region, FunctionalState NewState)
{
    if (NewState == ENABLE)
        BPK->BPK_LR |= BPK_LR_LOCK_KEYWRITE;
    else
        BPK->BPK_LR &= ~BPK_LR_LOCK_KEYWRITE;
    (void)BPK_KEY_Region;
}

void BPK_KeyReadLock(uint16_t BPK_KEY_Region, FunctionalState NewState)
{
    if (NewState == ENABLE)
        BPK->BPK_LR |= BPK_LR_LOCK_KEYREAD;
    else
        BPK->BPK_LR &= ~BPK_LR_LOCK_KEYREAD;
    (void)BPK_KEY_Region;
}

void BPK_KeyClear(uint16_t BPK_KEY_Region)
{
    BPK->BPK_CLR = BPK_KEY_Region;
}

void BPK_SetScramber(uint32_t Scram)
{
    BPK->BPK_SCR = Scram;
}

void BPK_Lock(uint32_t BPK_LOCK, FunctionalState NewState)
{
    if (NewState == ENABLE)
        BPK->BPK_LR |= (BPK_LOCK & BPK_LR_LOCK_ALL);
    else
        BPK->BPK_LR &= ~(BPK_LOCK & BPK_LR_LOCK_ALL);
}

void BPK_LockSelf(void)
{
    BPK->BPK_LR |= BPK_LR_LOCK_SELF;
}

FlagStatus BPK_GetLockStatus(uint32_t BPK_LOCK)
{
    return (BPK->BPK_LR & BPK_LOCK) ? SET : RESET;
}
