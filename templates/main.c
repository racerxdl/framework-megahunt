#include <stdio.h>
#include "air105.h"
#include "sysc.h"
#include "delay.h"
#include "uart.h"

int main(void) {
    SystemClock_Config_HSE();
    Delay_Init();
    USART_Init();
    SYSCTRL->CG_CTRL1 = SYSCTRL_APBPeriph_ALL;
    SYSCTRL->CG_CTRL2 = SYSCTRL_AHBPeriph_ALL;

    GPIO_InitTypeDef gpio;
    gpio.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Remap = GPIO_Remap_1;
    GPIO_Init(GPIOD, &gpio);

    Delay_ms(2000);
    printf("USART Init\r\n");
    printf("CHIP ID: %04x\r\n", SYSCTRL->CHIP_ID);

    while (1) {
        GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
        printf("RESET ");
        Delay_ms(1000);
        GPIO_SetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
        printf("SET\r\n");
        Delay_ms(1000);
    }
}