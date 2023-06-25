/* Copyright 2022 Ariamelon
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

#include "cantaloupe.h"
#include QMK_KEYBOARD_H

bool is_keyboard_master(void) {
    static bool determined = false;
    static bool is_master;
    if (!determined) {
        determined = true;
        setPinInput(SPLIT_PLUG_DETECT_PIN);
        wait_ms(1);
        is_master = (bool)readPin(SPLIT_PLUG_DETECT_PIN);
        if (!is_master) {
            usbStop(&USBD1);
        }
    }

    return is_master;
}

void board_init(void) {
    // B9 is configured as I2C1_SDA_PIN in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    setPinInputHigh(B9);
}