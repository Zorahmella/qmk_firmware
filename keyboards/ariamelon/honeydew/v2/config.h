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

#ifdef CONSOLE_ENABLE
#   undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#   define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1
#endif

#define SYSTEM_TIMEOUT 30000

// Matrix settings, must be done here due to custom matrix
#define MATRIX_ROWS 5
#define MATRIX_COLS 15
#define MATRIX_CS_PIN GP17
#define MATRIX_SPI_DIVISOR 16
#define MATRIX_SPI_MODE 3

#define ROWS {GP3, GP4, GP5, GP6, GP7}

// 0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000
// 1QA     1QB     1QC     1QD     1QE     1QF     1QG     1QH     2QA     2QB     2QC     2QD     2QE     2QF     2QG     2QH
// COL06   COL05   COL07   COL04   COL03   COL02   COL01   COL00   N/A     COL14   COL13   COL12   COL11   COL10   COL09   COL08
#define COLS {0x0080, 0x0040, 0x0020, 0x0010, 0x0008, 0x0002, 0x0001, 0x0004, 0x8000, 0x4000, 0x2000, 0x1000, 0x0800, 0x0400, 0x0200}

// ADC pin settings
#define VSEN_PIN GP29
#define ISEN_PIN GP28
#define VSEN_MAX 5000 // Max value of ADC reading in mV
#define ISEN_MAX 3000 // Max value of ADC reading in mA
#define VSEN_CAL 1.111 // ADC error calibration value
#define ADC_MAX 1023 // 10 bit ADC max number
#define ADC_EMA_ALPHA(x) ((uint16_t)(x * 65535)) // Alpha value of exponential moving average
#define ADC_UPDATE_TIME 10 // Time between ADC updates in ms

// TUSB321 pin settings
#define TUSB_OUT1_PIN GP27
#define TUSB_OUT2_PIN GP26

// ILIM fault settings
#define BOARD_ILIM_FLT_PIN GP25
#define RGB_ILIM_FLT_PIN GP20

// ILIM EN settings
#define ILIM_1500MA_PIN GP24
#define ILIM_3000MA_PIN GP23

// Pointing device settings
#define POINTING_DEVICE_CS_PIN GP14
#define POINTING_DEVICE_MOTION_PIN GP15

// Cirque settings
#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define POINTING_DEVICE_DRIVER cirque_pinnacle_spi
#define POINTING_DEVICE_ROTATION_90
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#undef CIRQUE_PINNACLE_ATTENUATION
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X

// QP OLED settings
#define SSD1351_WIDTH 128
#define SSD1351_HEIGHT 128
#define SSD1351_SPI_DIVISOR 16
#define SSD1351_SPI_MODE 3
#define SSD1351_CS_PIN GP13
#define SSD1351_DC_PIN GP12
#define SSD1351_RST_PIN NO_PIN
#undef QUANTUM_PAINTER_DISPLAY_TIMEOUT
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT SYSTEM_TIMEOUT
#undef QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   undef RGB_MATRIX_TIMEOUT
#   define RGB_MATRIX_TIMEOUT SYSTEM_TIMEOUT
#   define RGB_EN_PIN GP21
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#   define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#   define WS2812_DI_PIN GP22
#   define RGB_MATRIX_CENTER { 112, 80 }
#   define RGB_MATRIX_LED_COUNT 72
#endif
