#include "matrix.hpp"

#include <Arduino.h>
#include <util/atomic.h>

volatile matrix::rowmask_t matrix::screen_buf[32] = {0};

/** 
 * \brief Interrupt triggered by timer b that is used to display the LED matrix row by row
 */
ISR(TCA0_CMP0_vect) {
    static uint8_t row = 0;
    //Increment the currently displayed row or reset to the first row if we have displayed the last one
    row = (row >= 32) ? 0 : row + 2;
    const uint16_t rowbits = 0b1000000000000000 >> (row / 2);
    //asm(
    //  "cbi 0x9, 0 \n\t"
    //);
    //PORTC.OUT &= 0b01111111;
   digitalWrite(LATCH_PIN, LOW);
    //write lower 8 row bits to U4
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~(uint8_t)(rowbits));
    //write upper 8 row bits to U3
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, ~(uint8_t)(rowbits >> 8));

    //write lower 8 column bits to U2
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, matrix::screen_buf[row + 1]);
    //write upper 8 column bits to U1
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, matrix::screen_buf[row]);
    //asm(
    //  "sbi 0x9, 0 \n\t"
    //);
    digitalWrite(LATCH_PIN, HIGH);
    //TCA0.SINGLE.CNT = 0;
}
