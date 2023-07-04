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

// Reset button
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500

// SPI settings
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MISO_PIN GP16
#define SPI_MOSI_PIN GP19

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   define RGB_DISABLE_WHEN_USB_SUSPENDED
#   define WS2812_PIO_USE_PIO0
#   define RGB_MATRIX_LED_FLUSH_LIMIT 16
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_DEFAULT_HUE 0
#   define RGB_MATRIX_DEFAULT_SAT 0
#   define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#endif
