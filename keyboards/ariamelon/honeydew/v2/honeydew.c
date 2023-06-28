/* Copyright 2018-2023 Nick Brassel (@tzarc) 2023 Aria Tso (@Ariamelon)
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

#include "analog.h"
#include "quantum.h"
#include "qp.h"
#include "usbpd.h"
#include "adc.h"

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif

painter_device_t display; // QP display
static kb_runtime_config kb_state; // USB PD state
static float kb_scale; // USB PD RGB brightness scale
static adc_values current_adc_state; // Current ADC values
deferred_token ADC_READ;
static bool rgb_on;

// Initialize GPIO
void board_init(void) {
    // TUSB321 pin initialization
    setPinInput(TUSB_OUT1_PIN);
    setPinInput(TUSB_OUT2_PIN);
    kb_state.current_setting = USBPD_500MA;

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

// Keyboard initialization
void keyboard_post_init_kb(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable = true;
        debug_keyboard = true;
    #endif

    // SSD1351 display initialization
    display = qp_ssd1351_make_spi_device(SSD1351_WIDTH, SSD1351_HEIGHT, SSD1351_CS_PIN, SSD1351_DC_PIN, SSD1351_RST_PIN, SSD1351_SPI_DIVISOR, SSD1351_SPI_MODE);
    qp_init(display, QP_ROTATION_0);
    qp_power(display, true);
    qp_clear(display);

    // Get rgb matrix current state
    if (rgb_matrix_is_enabled()){
        writePinLow(RGB_EN_PIN);
        rgb_on = true;
    } else {
        rgb_on = false;
    }

    // Start up ADC reading code
    current_adc_state.volts = 0.0;
    current_adc_state.amps = 0.0;
    ADC_READ = defer_exec(1000, adc_get_values, NULL);

    // Allow for user post-init
    keyboard_post_init_user();
}

// Keyboard housekeeping
void housekeeping_task_kb(void) {
    // Update USB PD state
    bool usbpd_changed = usbpd_update();

    if (rgb_matrix_is_enabled() && !rgb_matrix_get_suspend_state()){
        if (rgb_on == false){
            // Enable RGB power
            dprintf("Enabling RGB power switch\n");
            writePinLow(RGB_EN_PIN);
            rgb_on = true;
        }

        // Toggles RGB ILIM switch based on if matrix is enabled or not
        if (usbpd_changed == true){
            dprintf("Toggling RGB\n");
            rgb_matrix_disable_noeeprom();
            rgb_matrix_enable_noeeprom();
        }
    } else if (rgb_on == true){
        // Disable RGB power
        dprintf("Disabling RGB power switch\n");
        writePinHigh(RGB_EN_PIN);
        rgb_on = false;
    }
}

// Gets USB PD current allowance
usbpd_allowance_t usbpd_get_allowance(void) {
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

// Get current ADC values
adc_values adc_update(adc_values next_adc_state){
    adc_values temp_adc_state;

    // Reading in raw values from ADC
    temp_adc_state.volts = analogReadPin(VSEN_PIN);
    temp_adc_state.amps = analogReadPin(ISEN_PIN);

    // Convert raw values into actual values
    next_adc_state.volts = temp_adc_state.volts / ADC_MAX * VSEN_MAX;
    next_adc_state.amps = temp_adc_state.amps / ADC_MAX * ISEN_MAX;

    return next_adc_state;
}

// Fetch ADC values once per second
uint32_t adc_get_values(uint32_t trigger_time, void *cb_arg) {
    current_adc_state = adc_update(current_adc_state);
    dprintf("Voltage = %.2fV, Current draw = %.2fA\n", current_adc_state.volts, current_adc_state.amps);
    return 1000;
}

// Code to run when keyboard sleeps
void suspend_power_down_kb(void) {
    // Turn off backlight
    qp_power(display, false);

    // Turn off RGB power
    rgb_matrix_set_suspend_state(true);

    suspend_power_down_user();
}

// Code to run when keyboard wakes up
void suspend_wakeup_init_kb(void) {
    // Turn on backlight
    qp_power(display, true);

    // Turn on RGB power
    rgb_matrix_set_suspend_state(false);

    suspend_wakeup_init_user();
}
