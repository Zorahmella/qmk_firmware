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

#include "quantum.h"
#include "usbpd.h"

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif

// Gets USB PD current allowance
usbpd_allowance_t usbpd_get_allowance(void) {
    /* TUSB_OUT = 0b000000ab
     *
     * a = TUSB_OUT1
     * b = TUSB_OUT2
     * x = ILIM_3000MA
     * y = ILIM_1500MA
     *
     * a | b | x | y
     * --------------
     * 0 | 0 | 1 | 1  High power
     * 0 | 1 | 0 | 1  Med power
     * 1 | x | 0 | 0  Default power
     */

    uint8_t TUSB_OUT = 0;

    TUSB_OUT |= readPin(TUSB_OUT2_PIN); // Set first bit to value of TUSB_OUT2
    TUSB_OUT |= (readPin(TUSB_OUT1_PIN) << 1); // Set second bit to value of TUSB_OUT1

    switch (TUSB_OUT){
        default:
            // 0.5A capable PSU is detected
            return USBPD_500MA;
        case 0: // 0b00000000
            // 3A capable PSU is detected
            return USBPD_3000MA;
        case 1: // 0b00000001
            // 1.5A capable PSU is detected
            return USBPD_1500MA;
    }
}

// Outputs USB PD state as a string
const char* usbpd_str(usbpd_allowance_t allowance) {
    switch (allowance) {
        default:
        case USBPD_500MA:
            return "500mA";
        case USBPD_1500MA:
            return "1500mA";
        case USBPD_3000MA:
            return "3000mA";
    }
}

// Updates USB PD state
bool usbpd_update(void) {
    static uint32_t last_read = 0;
    if (timer_elapsed32(last_read) > 250) {
        usbpd_allowance_t allowance = usbpd_get_allowance();
        if (kb_state.current_setting != allowance) {
            dprintf("Transitioning PD state %s -> %s\n", usbpd_str(kb_state.current_setting), usbpd_str(allowance));
            kb_state.current_setting = allowance;
            switch (allowance){
                case USBPD_500MA:
                    // 0.5A capable PSU behaviour
                    writePinLow(ILIM_1500MA_PIN);
                    writePinLow(ILIM_3000MA_PIN);
                    kb_scale = 0.35;
                    break;
                case USBPD_1500MA:
                    // 1.5A capable PSU is detected
                    writePinHigh(ILIM_1500MA_PIN);
                    writePinLow(ILIM_3000MA_PIN);
                    kb_scale = 0.65;
                    break;
                case USBPD_3000MA:
                    // 3A capable PSU is detected
                    writePinHigh(ILIM_1500MA_PIN);
                    writePinHigh(ILIM_3000MA_PIN);
                    kb_scale = 1.0;
                    break;
            }
            return true;
        }
    }
    return FALSE;
}

// RGB brightness scaling
#if defined(RGB_MATRIX_ENABLE)
RGB rgb_matrix_hsv_to_rgb(HSV hsv) {
    switch (kb_state.current_setting) {
        default:
        case USBPD_500MA:
            kb_scale = 0.35;
            break;
        case USBPD_1500MA:
            kb_scale = 0.65;
            break;
        case USBPD_3000MA:
            kb_scale = 1.0;
            break;
    }

    // Sets brightness according to scale
    hsv.v = (uint8_t)(hsv.v * kb_scale);
    return hsv_to_rgb(hsv);
}
#endif
