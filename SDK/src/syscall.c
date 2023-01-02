#include <stdio.h>
#include "air105.h"


int _write(int file, const char *ptr, size_t len) {
    if (file == 1) {
        for (int i = 0; i < len; i++) {
            while (!UART_IsTXEmpty(UART0));
            UART_SendData(UART0, (uint8_t)ptr[i]);
        }
    }

    // return the number of bytes passed (all of them)
    return len;
}
