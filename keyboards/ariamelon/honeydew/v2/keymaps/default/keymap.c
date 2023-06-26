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

#include QMK_KEYBOARD_H
#include "analog.h"

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif

enum keymap_layers {
    _BASE = 0,
    _FN,
    _CONFIG,
};

enum custom_keycodes {
    PRNTSCR = SAFE_RANGE,
    RGB_VII
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                       KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                       KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
        MO(2)  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                       KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,      KC_BTN2, KC_BTN1, KC_BTN2,       KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_SLSH,
        KC_DEL , KC_LGUI, KC_LALT,      MO(1)  , KC_LSFT, KC_BSPC,          KC_BTN3,          KC_ENT , KC_SPC , MO(1)  ,       KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                       KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
        _______, _______, KC_PGUP, _______, _______, _______,                                       _______, _______, _______, KC_PGUP, _______, _______,
        _______, KC_HOME, KC_PGDN, KC_END , KC_LBRC, KC_PLUS,                                       KC_MINS, KC_RBRC, KC_HOME, KC_PGDN, KC_END , _______,
        _______, _______, _______, _______, KC_LCBR, KC_EQL ,      KC_MPRV, KC_MPLY, KC_MNXT,       KC_UNDS, KC_RCBR, _______, _______, _______, _______,
        PRNTSCR, _______, _______,      _______, KC_CAPS, _______,          KC_MUTE,          _______, _______, _______,       _______, _______, _______
    ),

    [_CONFIG] = LAYOUT(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        XXXXXXX, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, XXXXXXX,                                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_RMOD,RGB_TOG, RGB_MOD,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX
    )
};

// Encoder map
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_FN] =     { ENCODER_CCW_CW(C(KC_Z), C(KC_Y))},
    [_CONFIG] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
};
#endif

void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable = true;
        debug_keyboard = true;
    #endif

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

    // Enables RGB if the RGB matrix is enabled
    if (rgb_matrix_is_enabled()){
        writePinLow(RGB_EN_PIN);
    }
}

// Hotkeys and macros
bool process_record_user(uint16_t keycode, keyrecord_t *record){
    switch (keycode) {
        // Snipping tool macro
        case PRNTSCR:
            if (record->event.pressed) {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LSFT);
                unregister_code(KC_LGUI);
            }
            return true;
        default:
            return true;
    }
}

void housekeeping_task_user(void) {
    // Reading in raw values from ADC
    float VSEN_RAW = analogReadPin(VSEN_PIN);
    float ISEN_RAW = analogReadPin(ISEN_PIN);

    // Convert raw values into actual values
    float VSEN = VSEN_RAW / ADC_MAX * VSEN_MAX;
    float ISEN = ISEN_RAW / ADC_MAX * ISEN_MAX;

    uprintf("V = %dmV, IDraw = %dmA\n", (int)VSEN, (int)ISEN);

    uint8_t TUSB_OUT = 0;

    /* TUSB_OUT = 0b000000ab
       a = TUSB_OUT1
       b = TUSB_OUT2
       x = ILIM_3000MA
       y = ILIM_1500MA

       a | b | x | y
       --------------
       0 | 0 | 1 | 1  High power
       0 | 1 | 0 | 1  Med power
       1 | x | 0 | 0  Default power
    */

    TUSB_OUT |= readPin(TUSB_OUT2_PIN); // Set first bit to value of TUSB_OUT2
    TUSB_OUT |= (readPin(TUSB_OUT1_PIN) << 1); // Set second bit to value of TUSB_OUT1

    float BRIGHTNESS_SCALE;
    switch (TUSB_OUT){
            case 0: // 0b00000000
            // 3A capable PSU is detected
            writePinHigh(ILIM_1500MA_PIN);
            writePinHigh(ILIM_3000MA_PIN);
            BRIGHTNESS_SCALE = 1.0f;
            break;
        case 1: // 0b00000001
            // 1.5A capable PSU is detected
            writePinHigh(ILIM_1500MA_PIN);
            writePinLow(ILIM_3000MA_PIN);
            BRIGHTNESS_SCALE = 0.5f;
            break;
        default:
            // Default behaviour
            writePinLow(ILIM_1500MA_PIN);
            writePinLow(ILIM_3000MA_PIN);
            BRIGHTNESS_SCALE = 0.35f;
            break;
    }

    // Toggles RGB ILIM switch based on if matrix is enabled or not
    uint8_t RGB_EN = rgb_matrix_is_enabled();
    switch (RGB_EN){
        case 1:
            writePinLow(RGB_EN_PIN);
            break;
        case 0:
            writePinHigh(RGB_EN_PIN);
    }

    // Limits max brightness depending on board power limit
    if (rgb_matrix_get_val() > RGB_MATRIX_MAXIMUM_BRIGHTNESS * BRIGHTNESS_SCALE){
        rgb_matrix_sethsv(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_MAXIMUM_BRIGHTNESS * BRIGHTNESS_SCALE);
    }
}
