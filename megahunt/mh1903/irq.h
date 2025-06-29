#pragma once

void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void DMA_IRQHandler(void);
void USB_IRQHandler(void);
void USBDMA_IRQHandler(void);
void LCD_IRQHandler(void);
void SCI0_IRQHandler(void);
void UART0_IRQHandler(void);
void UART1_IRQHandler(void);
void SPI0_IRQHandler(void);
void CRYPT0_IRQHandler(void);
void TIM_0_IRQHandler(void);
void TIM_1_IRQHandler(void);
void TIM_2_IRQHandler(void);
void TIM_3_IRQHandler(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void RTC_IRQHandler(void);
void SENSOR_IRQHandler(void);
void TRNG_IRQHandler(void);
void ADC0_IRQHandler(void);
void SSC_IRQHandler(void);
void TIM_4_IRQHandler(void);
void TIM_5_IRQHandler(void);
void KBD_IRQHandler(void);
void MSR_IRQHandler(void);
void EXTI3_IRQHandler(void);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);

void SCI2_IRQHandler(void);

void UART2_IRQHandler(void);
void UART3_IRQHandler(void);

void QSPI_IRQHandler(void);
void I2C0_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI5_IRQHandler(void);
void TIM_6_IRQHandler(void);
void TIM_7_IRQHandler(void);

void DCMI_IRQHandler(void);

void QR_IRQHandler(void);
void GPU_IRQHandler(void);

void AWD_IRQHandler(void);
void DAC_IRQHandler(void);
void SPI5_IRQHandler(void);

typedef void (*Handler)(void);

typedef struct{
	void* estack;
	Handler vector[255];
} Vectors;