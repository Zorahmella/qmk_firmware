/* Copyright 2023 Zorahmella
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

#include QMK_KEYBOARD_H

enum keymap_layers {
    _BASE = 0,
    _FN,
    _CONFIG,
};

enum custom_keycodes {
    PRNTSCR = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                       KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        MO(2)  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                       KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                                       KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_SLSH,
        KC_DEL , KC_LGUI, KC_LALT,      MO(1)  , KC_LSFT, KC_BSPC, KC_BTN2, KC_BTN1, KC_BTN2, KC_ENT , KC_SPC , MO(1)  ,       KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        _______, _______, KC_PGUP, _______, _______, _______,                                       _______, _______, _______, KC_PGUP, _______, _______,
        _______, KC_HOME, KC_PGDN, KC_END , KC_LBRC, KC_PLUS,                                       KC_MINS, KC_RBRC, KC_HOME, KC_PGDN, KC_END , _______,
        _______, _______, _______, _______, KC_LCBR, KC_EQL ,                                       KC_UNDS, KC_RCBR, _______, _______, _______, _______,
        PRNTSCR, _______, _______,      _______, KC_CAPS, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______,       _______, _______, _______
    ),

    [_CONFIG] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, XXXXXXX, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, RGB_RMOD,RGB_TOG, RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX
    )
};

// Hotkeys and macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PRNTSCR:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            break;
    }
  return true;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_FN] =     { ENCODER_CCW_CW(C(KC_Z), C(KC_Y))},
    [_CONFIG] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif
