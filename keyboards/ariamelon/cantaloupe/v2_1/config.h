/*
Copyright 2022 Ariamelon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Config*/
#define PRODUCT Cantaloupe
#define DEVICE_VER 0x0022

/* Matrix Config*/
#define MATRIX_ROW_PINS { A13, A15, B3, B4, B5 }
#define MATRIX_COL_PINS { A14, A8, B15, B14, B13, B12, B8 }

/* Encoder Config*/
#define ENCODERS_PAD_A { B9 }
#define ENCODERS_PAD_B { C13 }

#define ENCODERS_PAD_A_RIGHT { C13 }
#define ENCODERS_PAD_B_RIGHT { B9 }

/* Split Config*/
#define SPLIT_HAND_PIN B1
#define SPLIT_PLUG_DETECT_PIN B10
#define POINTING_DEVICE_COMBINED

/* WS2812 RGB LED */
#define RGB_DI_PIN B0
#define RGBLED_NUM 2
#define RGBLIGHT_ANIMATIONS
#define RGBLED_SPLIT { 1, 1 }

#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1

#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

/* SPI config */
#undef SPI_DRIVER
#define SPI_DRIVER SPID1

#undef SPI_SCK_PIN
#define SPI_SCK_PIN A5

#undef SPI_MOSI_PIN
#define SPI_MOSI_PIN A7

#undef SPI_MISO_PIN
#define SPI_MISO_PIN A6

#define CIRQUE_PINNACLE_SPI_CS_PIN A4
