// Copyright 2023 Zorah Tso (@Zorahmella)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// PMW3360 settings
#define PMW3360_MAX_CPI 12000
#define PMW3360_MIN_CPI 100
#define PMW3360_DEFAULT_CPI 800
#define POINTING_DEVICE_ROTATION_270
#define ROTATIONAL_TRANSFORM_ANGLE 90
#define POINTING_DEVICE_INVERT_Y

// RGB config
#ifdef RGB_MATRIX_ENABLE
#   undef RGB_MATRIX_TIMEOUT
#   define RGB_MATRIX_TIMEOUT 100000
#endif
