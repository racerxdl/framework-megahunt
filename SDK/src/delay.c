#include "delay.h"

#include "air105.h"

volatile uint32_t g_current_tick = 0;

void Delay_Init(void) {
    SysTick_Config(SYSCTRL->HCLK_1MS_VAL * 2 / 1000);
    /*
    or use the following equivalent

    SYSCTRL_ClocksTypeDef clocks;
    SYSCTRL_GetClocksFreq(&clocks);
    SysTick_Config(clocks.CPU_Frequency / 1000000);
    */
}

void SysTick_Handler(void) {
    g_current_tick++;
}

uint32_t get_tick(void) {
    return g_current_tick;
}

uint32_t get_diff_tick(uint32_t cur_tick, uint32_t prior_tick) {
    if (cur_tick < prior_tick) {
        return (cur_tick + (~prior_tick));
    } else {
        return (cur_tick - prior_tick);
    }
}

void Delay_us(uint32_t usec) {
    uint32_t old_tick;

    old_tick = g_current_tick;
    while (get_diff_tick(g_current_tick, old_tick) < usec)
        ;
}

void Delay_ms(uint32_t msec) {
    uint32_t old_tick;

    old_tick = g_current_tick;
    while (get_diff_tick(g_current_tick, old_tick) < (msec * 1000))
        ;
}
