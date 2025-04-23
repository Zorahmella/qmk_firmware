/* Copyright 2018-2023 Nick Brassel (@tzarc) 2023 Zorah Tso (@Zorahmella)
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

// Enumerated values for USB PD states
typedef enum {
    USBPD_500MA,
    USBPD_1500MA,
    USBPD_3000MA,
} usbpd_allowance_t;

// Structure to hold the USB PD current state
typedef struct kb_runtime_config {
    usbpd_allowance_t current_setting : 2;
} kb_runtime_config;

// Function to get PD allowance
usbpd_allowance_t usbpd_get_allowance(void);

// Function to update USB PD state
bool usbpd_update(void);

// Function to output USB PD state as a string
const char* usbpd_str(usbpd_allowance_t allowance);

kb_runtime_config kb_state; // USB PD state
float kb_scale; // USB PD RGB brightness scale
