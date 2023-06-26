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

void keyboard_pre_init_kb(void) {
    // TUSB321 pin initialization
    setPinInput(TUSB_OUT1_PIN);
    setPinInput(TUSB_OUT2_PIN);

    // ILIM fault pin initialization
    setPinInput(BOARD_ILIM_FLT_PIN);
    setPinInput(RGB_ILIM_FLT_PIN);

    // ILIM EN pin initialization
    setPinOutput(ILIM_1500MA_PIN);
    writePinLow(ILIM_1500MA_PIN);
    setPinOutput(ILIM_3000MA_PIN);
    writePinLow(ILIM_3000MA_PIN);

    // RGB EN pin initialization
    setPinOutput(RGB_EN_PIN);
    writePinHigh(RGB_EN_PIN);
}

void keyboard_post_init_kb(void) {
    uint8_t TUSB_OUT1 = readPin(TUSB_OUT1_PIN);
    uint8_t TUSB_OUT2 = readPin(TUSB_OUT2_PIN);
    if (TUSB_OUT1 = 0){
        writePinHigh(ILIM_1500MA_PIN);
        if (TUSB_OUT2 = 0){
            writePinHigh(ILIM_3000MA_PIN);
        }
    }
}

void matrix_scan_kb(void){
    if (rgb_matrix_is_enabled()){
        writePinLow(RGB_EN_PIN);
    } else {
        writePinHigh(RGB_EN_PIN);
    }
}
