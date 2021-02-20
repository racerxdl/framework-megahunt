////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Georgi Angelov ver 2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////////////////

#include <variant.h>
#include "hardware/gpio.h"
#include "hardware/adc.h"

void analogInit(uint8_t pin)
{
    static int adc_once = 0;
    if (!adc_once)
    {
        adc_once = 1;
        adc_init();
    }
    adc_gpio_init(pin); // Make sure GPIO is high-impedance, no pullups etc
}

INLINE int analogRead(uint8_t channel)
{
    adc_select_input(channel); // Select ADC input 0 (GPIO26)
    return adc_read();
}

void analogWrite(uint8_t channel, int val)
{
}

//void pwmInit(int channel, uint32_t count, pwm_osc_enum osc, bool start){}

void pwmStart(uint8_t channel, int val)
{
}

void pwmStop(uint8_t channel, int val)
{
}