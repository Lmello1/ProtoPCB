#include "matrix.hpp"

#include <Arduino.h>
#include <util/atomic.h>

volatile matrix::rowmask_t matrix::screen_buf[32] = {1};

/** 
 * \brief Interrupt triggered by timer b that is used to display the LED matrix row by row
 */
ISR(TCB0_INT_vect) {
    static uint8_t row = 0;
    //Increment the currently displayed row or reset to the first row if we have displayed the last one
    row = (row >= 32) ? 0 : row + 2;
    const uint16_t rowbits = 0b1000000000000000 >> (row / 2);
    digitalWrite(LATCH_PIN, LOW);
    //write lower 8 row bits to U4
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~(uint8_t)(rowbits));
    //write upper 8 row bits to U3
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~(uint8_t)(rowbits >> 8));

    //write lower 8 column bits to U2
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, matrix::screen_buf[row + 1]);
    //write upper 8 column bits to U1
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, matrix::screen_buf[row]);

    digitalWrite(LATCH_PIN, HIGH);
}
