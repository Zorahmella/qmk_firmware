// Copyright 2023 Aria Tso (@Ariamelon)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define FORCE_NKRO

// SPI settings
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 0
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 0
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 0

// Pointing device settings
#define POINTING_DEVICE_CS_PIN A4
#define MOUSE_EXTENDED_REPORT

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   define WS2812_PWM_DRIVER PWMD1
#   define WS2812_PWM_CHANNEL 1
#   define WS2812_PWM_PAL_MODE 2
#   define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#   define WS2812_DMA_CHANNEL 5
#   define WS2812_EXTERNAL_PULLUP
#   define RGB_DISABLE_WHEN_USB_SUSPENDED
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_DEFAULT_HUE 0
#   define RGB_MATRIX_DEFAULT_SAT 0
#   define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#   define RGB_MATRIX_CENTER { 112, 29 }
#   define RGB_MATRIX_LED_COUNT 72
#endif
