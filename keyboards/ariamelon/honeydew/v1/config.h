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

// Pointing device settings
#define POINTING_DEVICE_CS_PIN GP17
#define MOUSE_EXTENDED_REPORT

// Cirque settings
#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define POINTING_DEVICE_DRIVER cirque_pinnacle_spi
#define POINTING_DEVICE_ROTATION_90
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_TAP_ENABLE
#undef CIRQUE_PINNACLE_ATTENUATION
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X

/*
// QP OLED settings
#define DISPLAY_RST GP
#define DISPLAY_CS GP
#define DISPLAY_DC GP
*/

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   define WS2812_DI_PIN GP11
#   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#   define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
#   define RGB_MATRIX_CENTER { 112, 80 }
#   define RGB_MATRIX_LED_COUNT 69
#endif
