/* Copyright 2023 Aria Tso (@Ariamelon)
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

// Structure to hold ADC values
typedef struct adc_values_t {
    uint16_t volts;
    uint16_t amps;
} adc_values_t;

adc_values_t adc_update(adc_values_t next_adc_state); // Function to update ADC
uint16_t adc_ema(uint16_t in, uint16_t average, float alpha); // Exponential moving average function

// Deferred functions for getting ADC values and printing them
uint32_t adc_get_values(uint32_t trigger_time, void *cb_arg);
uint32_t adc_print_values(uint32_t trigger_time, void *cb_arg);

adc_values_t current_adc_state; // Current ADC values
