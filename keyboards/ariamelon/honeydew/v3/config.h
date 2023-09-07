/* Copyright 2023 Aria Tso (@Ariamelon)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define SYSTEM_TIMEOUT 30000

// SPI settings
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MISO_PIN A6
#define SPI_MOSI_PIN A7

// Pointing device settings
#define POINTING_DEVICE_CS_PIN A4

// Cirque settings
#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define POINTING_DEVICE_DRIVER cirque_pinnacle_spi
#define POINTING_DEVICE_ROTATION_270
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#undef CIRQUE_PINNACLE_ATTENUATION
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   define WS2812_PWM_DRIVER PWMD1
#   define WS2812_PWM_CHANNEL 1
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#   define WS2812_DMA_CHANNEL 5
#   define WS2812_EXTERNAL_PULLUP
#   define RGB_DISABLE_WHEN_USB_SUSPENDED
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_DEFAULT_HUE 0
#   define RGB_MATRIX_DEFAULT_SAT 0
#   define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#   define RGB_BRIGHTNESS_SCALAR 0.45
#   undef RGB_MATRIX_TIMEOUT
#   define RGB_MATRIX_TIMEOUT SYSTEM_TIMEOUT
#   define RGB_EN_PIN GP11
#   define RGB_MATRIX_CENTER { 112, 29 }
#   define RGB_MATRIX_LED_COUNT 72
#endif
