#pragma once

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#undef HAL_USE_SPI
#define HAL_USE_SPI TRUE
#undef SPI_USE_WAIT
#define SPI_USE_WAIT TRUE
#define SPI_SELECT_MODE SPI_SELECT_MODE_PAD

#include_next <halconf.h>
