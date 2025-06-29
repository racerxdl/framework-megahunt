#include "irq.h"

extern  unsigned int _estack;

__attribute__((section(".cortex_vectors")))
const Vectors cortex_vectors = {
	&_estack,
	{
        // OS handlers
		[0] = Reset_Handler,
		[1] = NMI_Handler,
		[2] = HardFault_Handler,
		[3] = MemManage_Handler,
		[4] = BusFault_Handler,
		[5] = UsageFault_Handler,

        [10] = SVC_Handler,
		[11] = DebugMon_Handler,
		[13] = PendSV_Handler,
		[14] = SysTick_Handler,
        // User defined IRQ handlers
		[15] = DMA_IRQHandler,
		[16] = USB_IRQHandler,
		[17] = USBDMA_IRQHandler,
		[18] = LCD_IRQHandler,
		[19] = SCI0_IRQHandler,
		[20] = UART0_IRQHandler,
		[21] = UART1_IRQHandler,
		[22] = SPI0_IRQHandler,
		[23] = CRYPT0_IRQHandler,
		[24] = TIM_0_IRQHandler,
		[25] = TIM_1_IRQHandler,
		[26] = TIM_2_IRQHandler,
		[27] = TIM_3_IRQHandler,
		[28] = EXTI0_IRQHandler,
		[29] = EXTI1_IRQHandler,
		[30] = EXTI2_IRQHandler,
		[31] = RTC_IRQHandler,
		[32] = SENSOR_IRQHandler,
		[33] = TRNG_IRQHandler,
		[34] = ADC0_IRQHandler,
		[35] = SSC_IRQHandler,
		[36] = TIM_4_IRQHandler,
		[37] = TIM_5_IRQHandler,
		[38] = KBD_IRQHandler,
		[39] = MSR_IRQHandler,
		[40] = EXTI3_IRQHandler,
		[41] = SPI1_IRQHandler,
		[42] = SPI2_IRQHandler,

		[44] = SCI2_IRQHandler,

		[47] = UART2_IRQHandler,
		[48] = UART3_IRQHandler,

		[50] = QSPI_IRQHandler,
		[51] = I2C0_IRQHandler,
		[52] = EXTI4_IRQHandler,
		[53] = EXTI5_IRQHandler,
		[54] = TIM_6_IRQHandler,
		[55] = TIM_7_IRQHandler,

		[57] = DCMI_IRQHandler,

		[61] = QR_IRQHandler,
		[62] = GPU_IRQHandler,

		[64] = AWD_IRQHandler,
		[65] = DAC_IRQHandler,
		[66] = SPI5_IRQHandler,
	},
};
