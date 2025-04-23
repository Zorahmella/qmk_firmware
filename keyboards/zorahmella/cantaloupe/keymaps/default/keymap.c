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
#include QMK_KEYBOARD_H
#include <stdio.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE = 0,
    _FN = 1,
    _POINT = 2,
    _NAV = 3
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    PRINTS = SAFE_RANGE,
    ALT_TAB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* BASE
* ,-----------------------------------------.                        ,-----------------------------------------.
* |  Esc |   1  |   2  |   3  |   4  |   5  |                        |   6  |   7  |   8  |   9  |   0  |   `  |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |  Tab |   Q  |   W  |   E  |   R  |   T  |                        |   Y  |   U  |   I  |   O  |   P  |   \  |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |  NAV |   A  |   S  |   D  |   F  |   G  |  ,----.       ,----.   |   H  |   J  |   K  |   L  |   ;  |   '  |
* |------+------+------+------+------+------| ( Play )     ( Play )  |------+------+------+------+------+------|
* | Ctrl |   Z  |   X  |   C  |   V  |   B  |  `----'       `----'   |   N  |   M  |   ,  |   .  |  Up  |   ?  |
* |------+------+------+------------------------.                ,------------------------+------+------+------|
* |  Del |  GUI |  Alt |   |Lower | Shift| Back |                | Enter| Space| Raise|   | Left | Down | Right|
* `--------------------'   `--------------------'                `--------------------'   `--------------------'
*
*/
    [_BASE] = LAYOUT( \
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                                  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
        KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,\
        MO(3)  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                  KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,\
        KC_LCTL, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,   KC_MPLY,            KC_MPLY,   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_SLSH,\
        KC_DEL , KC_LGUI, KC_LALT,    MO(1)  , KC_LSFT, KC_BSPC,                            KC_ENT , KC_SPC , MO(1)     , KC_LEFT, KC_DOWN, KC_RGHT \
    ),
/* FN
* ,-----------------------------------------.                        ,-----------------------------------------.
* |  F12 |  F1  |  F2  |  F3  |  F4  |  F5  |                        |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      |      | PgUp |      |      |      |                        |      |      |      | PgUp |      |      |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      | Home | PgDn |  End |   [  |   +  |  ,----.       ,----.   |   -  |   ]  | Home | PgDn |  End |      |
* |------+------+------+------+------+------| (      )     (      )  |------+------+------+------+------+------|
* |      |      |      |      |   {  |   =  |  `----'       `----'   |   _  |   }  |      |      |      |      |
* |------+------+------+------------------------.                ,------------------------+------+------+------|
* |PRINTS|      |      |   |      | Caps |  Del |                |      |      |      |   |      |      |      |
* `--------------------'   `--------------------'                `--------------------'   `--------------------'
*
*/
    [_FN] = LAYOUT( \
        KC_F12 , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                                 KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
        _______, _______, KC_PGUP, _______, _______, _______,                                 _______, _______, _______, KC_PGUP, _______, _______,\
        _______, KC_HOME, KC_PGDN, KC_END , KC_LBRC, KC_PLUS,                                 KC_MINS, KC_RBRC, KC_HOME, KC_PGDN, KC_END , _______,\
        _______, _______, _______, _______, KC_LCBR, KC_EQL ,   _______,          _______,    KC_UNDS, KC_RCBR, _______, _______, _______, _______,\
        PRINTS , _______, _______,    _______, KC_CAPS, KC_DEL ,                           _______, _______, _______,    _______, _______, _______ \
    ),
/* MOUSEKEYS
* ,-----------------------------------------.                        ,-----------------------------------------.
* |      |      |      |      |      |      |                        |      |      |      |      |      |      |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      |      |      |      |      |      |                        |      |      |      |      |      |      |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      |      |      |      |      |      |  ,----.       ,----.   |      |      |      |      |      |      |
* |------+------+------+------+------+------| (      )     (      )  |------+------+------+------+------+------|
* |      |      |      |      |      |      |  `----'       `----'   |      |      |      |      |      |      |
* |------+------+------+------------------------.                ,------------------------+------+------+------|
* |      |      |      |   |      |MouseL|MouseR|                |MouseL|MouseR|      |   |      |      |      |
* `--------------------'   `--------------------'                `--------------------'   `--------------------'
*
*/
    [_POINT] = LAYOUT( \
        _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,   _______,          _______,    _______, _______, _______, _______, _______, _______,\
        _______, _______, _______,    _______, KC_BTN1, KC_BTN2,                           KC_BTN1, KC_BTN2, _______,    _______, _______, _______ \
    ),
/* NAV
* ,-----------------------------------------.                        ,-----------------------------------------.
* |      |M_Acc0|M_Acc1|M_Acc2|      |      |                        |      |      |      |      |      |      |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      |      |      |      |      |      |                        |      |      |      |      |      |      |
* |------+------+------+------+------+------|                        |------+------+------+------+------+------|
* |      |      |      |      |      |      |  ,----.       ,----.   |      |      |      |      |      |      |
* |------+------+------+------+------+------| (      )     (      )  |------+------+------+------+------+------|
* |      |      |      |      |      |      |  `----'       `----'   |      |      |      |      |      |      |
* |------+------+------+------------------------.                ,------------------------+------+------+------|
* |      |      |      |   |      |      |      |                |      |      |      |   |      |      |      |
* `--------------------'   `--------------------'                `--------------------'   `--------------------'
*
*/
    [_NAV] = LAYOUT( \
        _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,                                 _______, _______, _______, _______, _______, _______,\
        _______, _______, _______, _______, _______, _______,   _______,          _______,    _______, _______, _______, _______, _______, _______,\
        _______, _______, _______,    _______, _______, _______,                           _______, _______, _______,    _______, _______, _______ \
    ),
};

void matrix_io_delay(void) {
    __asm__ volatile("nop\nnop\nnop\n");
}

// Hotkeys and macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PRINTS:
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

#ifdef POINTING_DEVICE_ENABLE

#define POINTER_TIMEOUT_MS 750
#define POINTER_TRIG_THRESHOLD 10
#define POINTER_SENSITIVITY 60000
#define SCROLL_SENSITIVITY 8000
static uint16_t auto_pointer_timer = 0;
bool set_scrolling = false;

#ifdef POINTING_DEVICE_COMBINED

;
    if (set_scrolling) {
        left_report.h = left_report.x;
        left_report.v = -1*left_report.y;
        left_report.x = 0;
        left_report.y = 0;
    }
    if (abs(left_report.x) > POINTER_TRIG_THRESHOLD || abs(left_report.y) > POINTER_TRIG_THRESHOLD ||
        abs(right_report.x) > POINTER_TRIG_THRESHOLD || abs(right_report.y) > POINTER_TRIG_THRESHOLD) {
        if (auto_pointer_timer == 0) {
            layer_on(_POINT);
        }
        auto_pointer_timer = timer_read();
    }
    return pointing_device_combine_reports(left_report, right_report);
}

#else
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _NAV:
        set_scrolling = TRUE;
        pointing_device_set_cpi(SCROLL_SENSITIVITY);
        break;
    default:
        set_scrolling = FALSE;
        pointing_device_set_cpi(POINTER_SENSITIVITY);
        break;
    }
  return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = -1*mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    if (abs(mouse_report.x) > POINTER_TRIG_THRESHOLD || abs(mouse_report.y) > POINTER_TRIG_THRESHOLD) {
        if (auto_pointer_timer == 0) {
            layer_on(_POINT);
        }
        auto_pointer_timer = timer_read();
    }
    return mouse_report;
}
#endif

#endif

#ifdef ENCODER_ENABLE

// Code for encoders
bool encoder_update_user(uint8_t index, bool clockwise) {
    layer_state_t current_state = get_highest_layer(layer_state);
    if (clockwise) {
        switch (current_state) {
            case _BASE:
            default:
                tap_code(KC_MNXT);
                break;
            case _FN:
                tap_code(KC_VOLU);
                break;
            case _NAV:
                tap_code16(C(KC_Y));
                break;
        }
    } else {
        switch (current_state) {
            case _BASE:
            default:
                tap_code(KC_MPRV);
                break;
            case _FN:
                tap_code(KC_VOLD);
                break;
            case _NAV:
                tap_code16(C(KC_Z));
                break;
        }
    }

    return false;
}
#endif

#ifdef OLED_ENABLE

bool gui_on = true;
char wpm_str[20];

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    oled_write_P(qmk_logo, false);
}

static void render_ariamelon_logo(void) {
    static const char PROGMEM ariamelon_logo[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x60, 0x30, 0x18,
0x08, 0x0c, 0xf2, 0x02, 0x06, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x38, 0xf8, 0xf0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0xc0, 0x60, 0x20, 0x30, 0x18, 0x0c, 0x04, 0x06, 0xc3, 0xe1, 0x60, 0x00, 0x02, 0x07, 0xc6,
0x70, 0x1f, 0x01, 0xc0, 0xfc, 0x0f, 0x00, 0x00, 0xe0, 0xe0, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
0xe6, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00,
0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x80,
0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0xff, 0x7f, 0x00, 0x00,
0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x80, 0x00, 0x00,
0x00, 0xc0, 0xc0, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x20, 0x30, 0x18, 0x0c, 0xf6, 0xe2, 0x03,
0x01, 0x00, 0x00, 0x06, 0x0f, 0x8c, 0x80, 0xc0, 0x40, 0x20, 0x30, 0x98, 0x8c, 0xc6, 0x63, 0x31,
0x0c, 0x06, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0xe0, 0xf0, 0xfe, 0xcf, 0x07, 0x03, 0x01, 0x00, 0x00, 0xc1, 0xff, 0x7f, 0x00, 0x00,
0xff, 0xff, 0x1f, 0x07, 0x0f, 0xfe, 0xfe, 0x0f, 0x07, 0x1f, 0xff, 0xff, 0x00, 0xf8, 0xff, 0xff,
0xe3, 0x71, 0x70, 0x38, 0x1d, 0x1f, 0x0f, 0x00, 0xc0, 0xf0, 0xff, 0xff, 0x8f, 0x00, 0x00, 0x00,
0x0e, 0x1f, 0x3b, 0xf1, 0xc1, 0x83, 0x03, 0x06, 0x06, 0x03, 0x83, 0xc1, 0xf1, 0xfb, 0x1f, 0x0e,
0x00, 0xff, 0xff, 0x0f, 0x03, 0x01, 0x01, 0x01, 0x03, 0x03, 0x0f, 0xff, 0xfc, 0x80, 0x00, 0x00,
0x00, 0x00, 0x0c, 0x1e, 0x33, 0x33, 0x66, 0x64, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
0x64, 0x66, 0x22, 0x33, 0x31, 0x11, 0x18, 0x08, 0x0c, 0x06, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x0c, 0x0e, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x07, 0x0f, 0x0f, 0x03, 0x03, 0x07, 0x0e, 0x0e, 0x0e, 0x0f, 0x0f, 0x07, 0x0e, 0x0c, 0x0c,
0x0f, 0x07, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x0e, 0x0f, 0x07, 0x07,
0x0e, 0x0e, 0x0c, 0x0c, 0x0c, 0x0e, 0x06, 0x07, 0x03, 0x03, 0x01, 0x07, 0x0f, 0x0e, 0x0c, 0x0e,
0x06, 0x07, 0x03, 0x03, 0x03, 0x03, 0x07, 0x0e, 0x0e, 0x07, 0x03, 0x01, 0x01, 0x03, 0x07, 0x0e,
0x0e, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x0f, 0x0f, 0x00, 0x00};
    oled_write_raw_P(ariamelon_logo, sizeof(ariamelon_logo));
}

static void master_side(void) {
    // QMK Logo
    render_qmk_logo();
    sprintf(wpm_str, "\nWPM: %03d\n", get_current_wpm());
    oled_write_P(wpm_str, false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("Function\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("Navigation\n"), false);
            break;
        case _POINT:
            oled_write_P(PSTR("Mouse layer\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
            break;
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(PSTR("Caps Lock: "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("On ") : PSTR("Off"), false);
}

static void slave_side(void) {
    // Ariamelon Logo
    render_ariamelon_logo();

    // WPM meter
    oled_set_cursor(0,5);
    oled_write_P(PSTR(" Cantaloupe Keyboard\n        V2.0"), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        master_side();
    } else {
        slave_side();
    }
    return false;
}

#endif

void matrix_scan_user(void) {
    #ifdef POINTING_DEVICE_ENABLE
    if (auto_pointer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_timer) >= POINTER_TIMEOUT_MS) {
        auto_pointer_timer = 0;
        layer_off(_POINT);
    }
    #endif
}

void keyboard_post_init_user(void) {
    #ifdef POINTING_DEVICE_ENABLE
    #ifdef POINTING_DEVICE_COMBINED
    pointing_device_set_cpi_on_side(true, SCROLL_SENSITIVITY);
    pointing_device_set_cpi_on_side(false, POINTER_SENSITIVITY);
    #endif
    #endif

    #ifdef CONSOLE_ENABLE
    debug_enable=true;
    #endif
}
