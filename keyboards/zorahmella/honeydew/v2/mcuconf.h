#pragma once

#include_next "mcuconf.h"

#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
