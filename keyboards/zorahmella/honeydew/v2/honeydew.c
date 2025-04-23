/* Copyright 2023 Zorah Tso (@Zorahmella)
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
#include "qp.h"
#include "usbpd.h"
#include "adc.h"

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif

painter_device_t display; // QP display
deferred_token ADC_READ, ADC_PRINT;

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

    // Start up ADC reading code
    current_adc_state = adc_update(current_adc_state);
    ADC_READ = defer_exec(10, adc_get_values, NULL);
    ADC_PRINT = defer_exec(1499, adc_print_values, NULL);

    // Allow for user post-init
    keyboard_post_init_user();
}

// Keyboard housekeeping
void housekeeping_task_kb(void) {
    static bool rgb_on = false;
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
