#pragma once

#define SERIAL_USB_BUFFERS_SIZE 256
#define HAL_USE_ADC TRUE
#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE
#undef SPI_USE_WAIT
#define SPI_USE_WAIT TRUE

#include_next <halconf.h>
