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

#include "adc.h"
#include "analog.h"
#include "quantum.h"

#ifdef CONSOLE_ENABLE
#   include "print.h"
#endif

// Get current ADC values
adc_values_t adc_update(adc_values_t next_adc_state){
    adc_values_t temp_adc_state;

    // Reading in raw values from ADC
    temp_adc_state.volts = analogReadPin(VSEN_PIN);
    temp_adc_state.amps = analogReadPin(ISEN_PIN);

    // Take exponential moving average of ADC values
    next_adc_state.volts = adc_ema(temp_adc_state.volts, next_adc_state.volts, ADC_EMA_ALPHA);
    next_adc_state.amps = adc_ema(temp_adc_state.amps, next_adc_state.amps, ADC_EMA_ALPHA);

    return next_adc_state;
}

// Exponential moving average
uint16_t adc_ema(uint16_t in, uint16_t average, float alpha){
    uint32_t tmp;
    tmp = (uint32_t)in * (1000000 * alpha) + (uint32_t)average * (1000000 - (1000000 * alpha));
    return (uint16_t)((tmp + 500000) / 1000000);
}

// Fetch ADC values based on ADC_UPDATE_TIME
uint32_t adc_get_values(uint32_t trigger_time, void *cb_arg) {
    current_adc_state = adc_update(current_adc_state);
    return ADC_UPDATE_TIME;
}

// Print ADC values once per second
uint32_t adc_print_values(uint32_t trigger_time, void *cb_arg) {
    adc_values_t temp_adc_state;

    // Convert raw values into actual values
    temp_adc_state.volts = current_adc_state.volts * (VSEN_MAX * VSEN_CAL) / ADC_MAX;
    temp_adc_state.amps = current_adc_state.amps * ISEN_MAX / ADC_MAX;

    dprintf("Voltage = %dmV, Current draw = %dmA\n", temp_adc_state.volts, temp_adc_state.amps);
    return 1000;
}
