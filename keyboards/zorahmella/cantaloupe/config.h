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

#ifdef CONSOLE_ENABLE
#define DEBUG_MATRIX_SCAN_RATE
#endif

/* MCU Config*/
#define STM32_HSECLK 8000000U

/* USB Config*/
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO
#define VENDOR_ID    0x4172 // Ar
#define PRODUCT_ID   0x4361 // Ca
#define MANUFACTURER Ariamelon

/* Matrix Config*/
#define MATRIX_ROWS 10
#define MATRIX_COLS 7
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5

/* Encoder Config*/
#define ENCODER_RESOLUTION 2

/* Split Config*/
#define FORCED_SYNC_THROTTLE_MS 500
#define SPLIT_MAX_CONNECTION_ERRORS 3
#define SPLIT_CONNECTION_CHECK_TIMEOUT 1000
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_POINTING_ENABLE

/* CRC Driver */
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* Serial Split Driver */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_SPEED 921600
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10

/* OLED Config */
#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 60000
#define OLED_UPDATE_INTERVAL 100

/* Mouse config */
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0

#define POINTING_DEVICE_TASK_THROTTLE_MS 1
