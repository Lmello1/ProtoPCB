#include <Arduino.h>
#include <util/atomic.h>

static constexpr uint8_t LATCH_PIN = 12;
static constexpr uint8_t CLOCK_PIN = 13;
static constexpr uint8_t DATA_PIN = 9;

/** \brief Constant passed to the `set` function to turn an LED on, so we can eliminate an unneeded bitshift */
static constexpr uint16_t LED_ON = 0b1000000000000000;

/** 
 * How a single row of the LED matrix is stored,
 * here every bit in the number indicates if the LED should be on or off
 */
using rowmask_t = uint16_t;

/** 
 * \brief Buffer containing bitmasks for each row in the matrix display.
 * Note that this buffer is frequently read by the matrix drawing interrupt, so to avoid 
 * scrambled data, any mutation of this variable should be surrounded in an ATOMIC_BLOCK, which disables interrupts
 * temporarily
 */
static volatile rowmask_t matrix_buf[16] = {0};

/**
 * Set or unset an LED in the matrix display by (x, y) coordinates
 */
inline void set(uint8_t x, uint8_t y, uint8_t on) {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        matrix_buf[y] = (matrix_buf[y] & ~(LED_ON >> x)) | (matrix_buf[y] | (on >> x));
    }
}


void setup(void) {
    matrix_buf[0]  = 0b0000000000000000;
    matrix_buf[1]  = 0b0000000000000000;
    matrix_buf[2]  = 0b0000000000000000;
    matrix_buf[3]  = 0b0000000000000000;
    matrix_buf[4]  = 0b0010000000000100;
    matrix_buf[5]  = 0b0000000000000000;
    matrix_buf[6]  = 0b0000000000000000;
    matrix_buf[7]  = 0b0100000000000010;
    matrix_buf[8]  = 0b0010000000000100;
    matrix_buf[9]  = 0b0001100000011000;
    matrix_buf[10] = 0b0000011111100000;
    matrix_buf[11] = 0b0000000000000000;
    matrix_buf[12] = 0b0000000000000000;
    matrix_buf[13] = 0b0000000000000000;
    matrix_buf[14] = 0b0000000000000000;
    matrix_buf[15] = 0b0000000000000000;

    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        //https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny3224-3226-3227-Data-Sheet-DS40002345A.pdf#_OPENTOPIC_TOC_PROCESSING_d5209e60328
        TCB0.CCMP = 4200; //nice
        TCB0.INTCTRL = 000000001;
        TCB0.CTRLA |= (1 << TCB_ENABLE_bp) | TCB_CLKSEL_DIV2_gc;
    }
}


void loop(void) {
    
}

/** 
 * \brief Interrupt triggered by timer b that is used to display the LED matrix row by row
 */
ISR(TCB0_INT_vect) {
    static uint8_t row = 0;
    //Increment the currently displayed row or reset to the first row if we have displayed the last one
    row = (row >= 16) ? 0 : row + 1;
    uint16_t rowbits = 0b1000000000000000 >> row;
    digitalWrite(LATCH_PIN, LOW);
    //write lower 8 row bits to U4
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~(uint8_t)(rowbits));
    //write upper 8 row bits to U3
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, ~(uint8_t)(rowbits >> 8));

    //write lower 8 column bits to U2
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(matrix_buf[row]));
    //write upper 8 column bits to U1
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(matrix_buf[row] >> 8));

    digitalWrite(LATCH_PIN, HIGH);
}
