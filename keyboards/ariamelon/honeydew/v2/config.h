/* Copyright 2023 Ariamelon
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

// Matrix settings, must be done here due to custom matrix

#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_CS_PIN GP1
#define MATRIX_SPI_DIVISOR 64
#define MATRIX_SPI_MODE 3

#define ROWS {GP3, GP4, GP5, GP6, GP7}

//0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
// 1QA     1QB     1QC     1QD     1QE     1QF     1QG     1QH     2QA     2QB     2QC     2QD     2QE     2QF     2QG     2QH
// COL06   COL05   COL07   COL04   COL03   COL02   COL01   COL00   N/A     COL14   COL13   COL12   COL11   COL10   COL09   COL08
#define COLS {0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0002, 0x0001, 0x0004, 0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200}

//TUSB321 pin settings
#define TUSB

// SPI settings
#define POINTING_DEVICE_CS_PIN GP14

/*
// QP OLED settings
#define DISPLAY_RST GP
#define DISPLAY_CS GP
#define DISPLAY_DC GP
*/

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 5
#   undef RGB_MATRIX_DEFAULT_VAL
#   define RGB_MATRIX_DEFAULT_VAL 5
#   define WS2812_DI_PIN GP22
#   define RGB_MATRIX_CENTER { 112, 80 }
#   define RGB_MATRIX_LED_COUNT 72
#endif
