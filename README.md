# framework-megahunt

MH190X (Air105) bare-metal SDK for PlatformIO.

## Supported SoCs

| Board    | SoC       | RAM    | Flash  |
|----------|-----------|--------|--------|
| AIR105   | MH1903    | 640 KB | 4 MB   |
| MH1903   | MH1903    | 1 MB   | 1 MB   |

## Architecture

- **CMSIS-Core** — Cortex-M4 device headers, system init
- **Peripheral Library** — Low-level register drivers (GPIO, UART, SPI, I2C, ADC, DAC, DMA, Timer, RTC, WDT, etc.)
- **HAL** — High-level abstractions with DMA and interrupt callbacks
- **USB Stack** — CDC (serial), HID, MSC (mass storage)
- **Device Drivers** — SPI flash (W25Q80BV), SDHC over SPI

## Requirements

- `arm-none-eabi-gcc` toolchain
- `python3` with `pycryptodome` (for upload)
