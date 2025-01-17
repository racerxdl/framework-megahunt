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

#ifndef __BL_INC_H__
#define __BL_INC_H__
#include "global_config.h"
#ifdef __AIR105_BSP__
#include "air105.h"
#include "air105_conf.h"
#endif
#include "bsp_common.h"
#include "platform_define.h"
#include "resource_map.h"
#include "core_dma.h"
#include "core_tick.h"
#include "core_debug.h"
#include "core_gpio.h"
#include "core_timer.h"
#include "core_uart.h"
#include "core_i2c.h"
#include "core_pm.h"
#include "core_spi.h"
#include "core_soft_keyboard.h"

#include "usb_driver.h"
#include "usb_device.h"
#include "usb_host.h"
#include "usb_msc.h"
#include "usb_hid.h"
#include "usb_scsi.h"
#include "usb_cdc.h"

#include "dev_spiflash.h"
#include "dev_sdhc_spi.h"
#endif
