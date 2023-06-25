#include "quantum.h"

#include "wait.h"
#include "spi_master.h"

static const uint16_t col_values[MATRIX_COLS] = COLS;
static const pin_t row_pins[MATRIX_ROWS] = ROWS;

static inline uint8_t read_rows(void) {
    uint8_t r = 0;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        r |= (readPin(row_pins[row]) << row);
    }
    return r;
}

static inline void shift_out(uint16_t value) {

    uint8_t message[2]  = {(value >> 8) & 0xFF ,(uint8_t)(value & 0xFF) };

    spi_start(MATRIX_CS_PIN, false, MATRIX_SPI_MODE, MATRIX_SPI_DIVISOR);
    spi_transmit(message,2);
    spi_stop();
}

static inline void select_col(uint8_t col) {
    shift_out(col_values[col]);
}

void matrix_init_custom(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        setPinInputLow(row_pins[row]);
    }

    spi_init();
    setPinOutput(MATRIX_CS_PIN);
    matrix_io_delay();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t temp_matrix[MATRIX_ROWS] = {0};

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);

        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            temp_matrix[row] |= (((rows & (1 << row))? 1 : 0) << col);
        }
    }

    bool changed = memcmp(current_matrix, temp_matrix, sizeof(temp_matrix));
    if (changed){
        memcpy(current_matrix, temp_matrix, sizeof(temp_matrix));
    }
    return changed;
}
