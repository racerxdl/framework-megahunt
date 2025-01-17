/*
 * Copyright (c) 2022 OpenLuat & AirM2M
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __PLATFORM_DEFINE_H__
#define __PLATFORM_DEFINE_H__
enum
{
	UART_DATA_BIT5 = 5,
	UART_DATA_BIT6 = 6,
	UART_DATA_BIT7 = 7,
	UART_DATA_BIT8 = 8,
	UART_DATA_BIT9 = 9,
	UART_PARITY_NONE = 0,
	UART_PARITY_ODD,
	UART_PARITY_EVEN,
	UART_STOP_BIT1 = 0,
	UART_STOP_BIT1_5,
	UART_STOP_BIT2,

	I2C_OP_READ_REG = 0,	//i2c通用读寄存器，一写一读，自动带start信号
	I2C_OP_READ,		//i2c通用读，只读
	I2C_OP_WRITE,		//i2c通用写，只写

	OP_QUEUE_CMD_END = 0,
	OP_QUEUE_CMD_ONE_TIME_DELAY,	//只有一次delay
	OP_QUEUE_CMD_CONTINUE_DELAY,	//连续delay，配合OP_QUEUE_CMD_REPEAT_DELAY使用
	OP_QUEUE_CMD_REPEAT_DELAY,	//重复OP_QUEUE_CMD_CONTINUE_DELAY
	OP_QUEUE_CMD_SET_GPIO_DIR_OUT,
	OP_QUEUE_CMD_SET_GPIO_DIR_IN,
	OP_QUEUE_CMD_GPIO_OUT,
	OP_QUEUE_CMD_GPIO_IN,
	OP_QUEUE_CMD_GPIO_IN_CB,
	OP_QUEUE_CMD_CB,
	OP_QUEUE_CMD_CAPTURE_SET,
	OP_QUEUE_CMD_CAPTURE,
	OP_QUEUE_CMD_CAPTURE_CB,
	OP_QUEUE_CMD_CAPTURE_END,
	OP_QUEUE_CMD_IO_PULL_NONE = 0,
	OP_QUEUE_CMD_IO_PULL_UP,
	OP_QUEUE_CMD_IO_PULL_DOWN,

	OP_QUEUE_CMD_IO_EXTI_UP = 0,		//上升沿中断
	OP_QUEUE_CMD_IO_EXTI_DOWN,		//下降沿中断
	OP_QUEUE_CMD_IO_EXTI_BOTH,	//双边沿中断

	COLOR_MODE_RGB_565 = 0,
	COLOR_MODE_GRAY,
	COLOR_MODE_RGB_888,
	COLOR_MODE_YCBCR_422_UYVY,
	COLOR_MODE_YCBCR_422_YUYV,
	COLOR_MODE_YCBCR_422_CBYCRY,

	CORE_OTA_MODE_FULL = 0,	//param1的byte0
	CORE_OTA_MODE_DIFF,
	CORE_OTA_IN_FLASH = 0,	//param1的byte1
	CORE_OTA_OUT_SPI_FLASH,
	CORE_OTA_IN_FILE,

};

enum
{
	USB_ID0 = 0,
	USB_MAX,
	I2C_ID0 = 0,
	I2C_MAX,
	UART_ID0 = 0,
	UART_ID1,
	UART_ID2,
	UART_ID3,
//	UART_ID4,
//	UART_ID5,
	UART_MAX,
	VIRTUAL_UART0 = 0,
	VIRTUAL_UART_MAX,
	HSPI_ID0 = 0,
	SPI_ID0,
	SPI_ID1,
	SPI_ID2,
	SPI_ID3,
	SPI_MAX,

	SPI_MODE_0 = 0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3,

	HW_TIMER0 = 0,
	HW_TIMER1,
	HW_TIMER2,
	HW_TIMER3,
	HW_TIMER4,
	HW_TIMER5,
	HW_TIMER_MAX,

	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_MAX,

	DMA1_STREAM_0 = 0,
	DMA1_STREAM_1,
	DMA1_STREAM_2,
	DMA1_STREAM_3,
	DMA1_STREAM_4,
	DMA1_STREAM_5,
	DMA1_STREAM_6,
	DMA1_STREAM_7,
	DMA1_STREAM_QTY,
	DMA_STREAM_QTY = DMA1_STREAM_QTY,

	HAL_GPIO_0 = 0,
	HAL_GPIO_1,
	HAL_GPIO_2,
	HAL_GPIO_3,
	HAL_GPIO_4,
	HAL_GPIO_5,
	HAL_GPIO_6,
	HAL_GPIO_7,
	HAL_GPIO_8,
	HAL_GPIO_9,
	HAL_GPIO_10,
	HAL_GPIO_11,
	HAL_GPIO_12,
	HAL_GPIO_13,
	HAL_GPIO_14,
	HAL_GPIO_15,
	HAL_GPIO_16,
	HAL_GPIO_17,
	HAL_GPIO_18,
	HAL_GPIO_19,
	HAL_GPIO_20,
	HAL_GPIO_21,
	HAL_GPIO_22,
	HAL_GPIO_23,
	HAL_GPIO_24,
	HAL_GPIO_25,
	HAL_GPIO_26,
	HAL_GPIO_27,
	HAL_GPIO_28,
	HAL_GPIO_29,
	HAL_GPIO_30,
	HAL_GPIO_31,
	HAL_GPIO_32,
	HAL_GPIO_33,
	HAL_GPIO_34,
	HAL_GPIO_35,
	HAL_GPIO_36,
	HAL_GPIO_37,
	HAL_GPIO_38,
	HAL_GPIO_39,
	HAL_GPIO_40,
	HAL_GPIO_41,
	HAL_GPIO_42,
	HAL_GPIO_43,
	HAL_GPIO_44,
	HAL_GPIO_45,
	HAL_GPIO_46,
	HAL_GPIO_47,
	HAL_GPIO_48,
	HAL_GPIO_49,
	HAL_GPIO_50,
	HAL_GPIO_51,
	HAL_GPIO_52,
	HAL_GPIO_53,
	HAL_GPIO_54,
	HAL_GPIO_55,
	HAL_GPIO_56,
	HAL_GPIO_57,
	HAL_GPIO_58,
	HAL_GPIO_59,
	HAL_GPIO_60,
	HAL_GPIO_61,
	HAL_GPIO_62,
	HAL_GPIO_63,
	HAL_GPIO_64,
	HAL_GPIO_65,
	HAL_GPIO_66,
	HAL_GPIO_67,
	HAL_GPIO_68,
	HAL_GPIO_69,
	HAL_GPIO_70,
	HAL_GPIO_71,
	HAL_GPIO_72,
	HAL_GPIO_73,
	HAL_GPIO_74,
	HAL_GPIO_75,
	HAL_GPIO_76,
	HAL_GPIO_77,
	HAL_GPIO_78,
	HAL_GPIO_79,
	HAL_GPIO_80,
	HAL_GPIO_81,
	HAL_GPIO_82,
	HAL_GPIO_83,
	HAL_GPIO_84,
	HAL_GPIO_85,
	HAL_GPIO_86,
	HAL_GPIO_87,
	HAL_GPIO_88,
	HAL_GPIO_89,
	HAL_GPIO_90,
	HAL_GPIO_91,
	HAL_GPIO_92,
	HAL_GPIO_93,
	HAL_GPIO_94,
	HAL_GPIO_95,
	HAL_GPIO_MAX,
	HAL_GPIO_NONE = HAL_GPIO_MAX, //大于等于HAL_GPIO_NONE，说明不存在
};

enum
{
	GPIOA_00 = 0,
	GPIOA_01,
	GPIOA_02,
	GPIOA_03,
	GPIOA_04,
	GPIOA_05,
	GPIOA_06,
	GPIOA_07,
	GPIOA_08,
	GPIOA_09,
	GPIOA_10,
	GPIOA_11,
	GPIOA_12,
	GPIOA_13,
	GPIOA_14,
	GPIOA_15,
	GPIOB_00,
	GPIOB_01,
	GPIOB_02,
	GPIOB_03,
	GPIOB_04,
	GPIOB_05,
	GPIOB_06,
	GPIOB_07,
	GPIOB_08,
	GPIOB_09,
	GPIOB_10,
	GPIOB_11,
	GPIOB_12,
	GPIOB_13,
	GPIOB_14,
	GPIOB_15,
	GPIOC_00,
	GPIOC_01,
	GPIOC_02,
	GPIOC_03,
	GPIOC_04,
	GPIOC_05,
	GPIOC_06,
	GPIOC_07,
	GPIOC_08,
	GPIOC_09,
	GPIOC_10,
	GPIOC_11,
	GPIOC_12,
	GPIOC_13,
	GPIOC_14,
	GPIOC_15,
	GPIOD_00,
	GPIOD_01,
	GPIOD_02,
	GPIOD_03,
	GPIOD_04,
	GPIOD_05,
	GPIOD_06,
	GPIOD_07,
	GPIOD_08,
	GPIOD_09,
	GPIOD_10,
	GPIOD_11,
	GPIOD_12,
	GPIOD_13,
	GPIOD_14,
	GPIOD_15,
	GPIOE_00,
	GPIOE_01,
	GPIOE_02,
	GPIOE_03,
	GPIOE_04,
	GPIOE_05,
	GPIOE_06,
	GPIOE_07,
	GPIOE_08,
	GPIOE_09,
	GPIOE_10,
	GPIOE_11,
	GPIOE_12,
	GPIOE_13,
	GPIOE_14,
	GPIOE_15,
	GPIOF_00,
	GPIOF_01,
	GPIOF_02,
	GPIOF_03,
	GPIOF_04,
	GPIOF_05,
	GPIOF_06,
	GPIOF_07,
	GPIOF_08,
	GPIOF_09,
	GPIOF_10,
	GPIOF_11,
	GPIOF_12,
	GPIOF_13,
	GPIOF_14,
	GPIOF_15,
	GPIO_MAX,
	GPIO_NONE = GPIO_MAX, //大于等于GPIO_NONE，说明不存在
};

#endif

#ifdef __AIR106_BSP__
enum
{
	LCD_ID0 = 0,
	LCD_MAX,
	USB_ID0 = 0,
	USB_MAX,
	CAN_ID0 = 0,	//CAN CLK=SYS/2
	CAN_ID1,
	CAN_MAX,
	I2C_ID0 = 0,	//I2C CLK=SYS/2
	I2C_ID1,
	I2C_MAX,
	UART_ID0 = 0,
	UART_ID1,
	UART_ID2,
	UART_ID3,
	UART_MAX,
	VIRTUAL_UART0 = 0,
	VIRTUAL_UART_MAX,

	SPI_ID0 = 0,
	SPI_ID1,
	SPI_MAX,

	SPI_MODE_0 = 0,
	SPI_MODE_1,
	SPI_MODE_2,
	SPI_MODE_3,

	HW_TIMER0 = 0,
	HW_TIMER1,
	HW_TIMER2,
	HW_TIMER3,
	HW_TIMER4,
	//下面是普通定时器
	HW_TIMER5,
	HW_TIMER6,
	HW_TIMER7,
	HW_TIMER8,
	HW_TIMER9,
	HW_TIMER10,
	HW_TIMER11,
	HW_TIMER12,
	HW_TIMER13,
	HW_TIMER14,

	HW_TIMER_MAX,

	ADC_CHANNEL_0 = 0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_MAX,

	DMA1_STREAM_0 = 0,
	DMA1_STREAM_1,
	DMA1_STREAM_2,
	DMA1_STREAM_3,
	DMA1_STREAM_QTY,
	DMA_STREAM_QTY = DMA1_STREAM_QTY,

	HAL_GPIO_MAX = 112,
	HAL_GPIO_NONE = HAL_GPIO_MAX, //大于等于HAL_GPIO_NONE，说明不存在
};


enum
{
	GPIOA_00 = 0,
	GPIOA_01,
	GPIOA_02,
	GPIOA_03,
	GPIOA_04,
	GPIOA_05,
	GPIOA_06,
	GPIOA_07,
	GPIOA_08,
	GPIOA_09,
	GPIOA_10,
	GPIOA_11,
	GPIOA_12,
	GPIOA_13,
	GPIOA_14,
	GPIOA_15,
	GPIOB_00,
	GPIOB_01,
	GPIOB_02,
	GPIOB_03,
	GPIOB_04,
	GPIOB_05,
	GPIOB_06,
	GPIOB_07,
	GPIOB_08,
	GPIOB_09,
	GPIOB_10,
	GPIOB_11,
	GPIOB_12,
	GPIOB_13,
	GPIOB_14,
	GPIOB_15,
	GPIOC_00,
	GPIOC_01,
	GPIOC_02,
	GPIOC_03,
	GPIOC_04,
	GPIOC_05,
	GPIOC_06,
	GPIOC_07,
	GPIOC_08,
	GPIOC_09,
	GPIOC_10,
	GPIOC_11,
	GPIOC_12,
	GPIOC_13,
	GPIOC_14,
	GPIOC_15,
	GPIOD_00,
	GPIOD_01,
	GPIOD_02,
	GPIOD_03,
	GPIOD_04,
	GPIOD_05,
	GPIOD_06,
	GPIOD_07,
	GPIOD_08,
	GPIOD_09,
	GPIOD_10,
	GPIOD_11,
	GPIOD_12,
	GPIOD_13,
	GPIOD_14,
	GPIOD_15,
	GPIOE_00,
	GPIOE_01,
	GPIOE_02,
	GPIOE_03,
	GPIOE_04,
	GPIOE_05,
	GPIOE_06,
	GPIOE_07,
	GPIOE_08,
	GPIOE_09,
	GPIOE_10,
	GPIOE_11,
	GPIOE_12,
	GPIOE_13,
	GPIOE_14,
	GPIOE_15,
	GPIOM_00,
	GPIOM_01,
	GPIOM_02,
	GPIOM_03,
	GPIOM_04,
	GPIOM_05,
	GPIOM_06,
	GPIOM_07,
	GPIOM_08,
	GPIOM_09,
	GPIOM_10,
	GPIOM_11,
	GPIOM_12,
	GPIOM_13,
	GPIOM_14,
	GPIOM_15,
	GPION_00,
	GPION_01,
	GPION_02,
	GPION_03,
	GPION_04,
	GPION_05,
	GPION_06,
	GPION_07,
	GPION_08,
	GPION_09,
	GPION_10,
	GPION_11,
	GPION_12,
	GPION_13,
	GPION_14,
	GPION_15,
	GPIO_MAX,
	GPIO_NONE = GPIO_MAX, //大于等于GPIO_NONE，说明不存在
};

#endif
