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
#define DEVICE_VER 0x0201

/* Matrix Config*/
#define MATRIX_ROW_PINS { B15, B14, A6, A5, A4 }
#define MATRIX_COL_PINS { B13, B12, B10, B1, B0, A7, A2 }

/* Encoder Config*/
#define ENCODERS_PAD_A { B5 }
#define ENCODERS_PAD_B { A3 }

#define ENCODERS_PAD_A_RIGHT { A3 }
#define ENCODERS_PAD_B_RIGHT { B5 }

/* Split Config*/
#define SPLIT_HAND_PIN C13
#define SPLIT_PLUG_DETECT_PIN A8
#define POINTING_DEVICE_RIGHT

/* Pimoroni Config */
#undef PIMORONI_TRACKBALL_SCALE
#define PIMORONI_TRACKBALL_SCALE 2
