#include "matrix.hpp"
#include <Arduino.h>
#include <util/atomic.h>

static constexpr uint8_t BUTTON_1 = 15;
static constexpr uint8_t BUTTON_2 = 16;
static constexpr uint8_t BUTTON_3 = 17;

void setup(void) {
    matrix::setrow(0,  0b0000000000000000);
    matrix::setrow(1,  0b0000000000000000);
    matrix::setrow(2,  0b0000000000000000);
    matrix::setrow(3,  0b0000000000000000);
    matrix::setrow(4,  0b0010000000000100);
    matrix::setrow(5,  0b0000000000000000);
    matrix::setrow(6,  0b0000000000000000);
    matrix::setrow(7,  0b0100000000000010);
    matrix::setrow(8,  0b0010000000000100);
    matrix::setrow(9,  0b0001100000011000);
    matrix::setrow(10, 0b0000011111100000);
    matrix::setrow(11, 0b0000000000000000);
    matrix::setrow(12, 0b0000000000000000);
    matrix::setrow(13, 0b0000000000000000);
    matrix::setrow(14, 0b0000000000000000);
    matrix::setrow(15, 0b0000000000000000);

    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        //https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny3224-3226-3227-Data-Sheet-DS40002345A.pdf#_OPENTOPIC_TOC_PROCESSING_d5209e60328
        TCB0.CCMP = 42000; //nice
        TCB0.INTCTRL = 000000001;
        TCB0.CTRLA |= (1 << TCB_ENABLE_bp) | TCB_CLKSEL_DIV2_gc;
    }
}


void loop(void) {
    
}
