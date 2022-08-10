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
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        //https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny3224-3226-3227-Data-Sheet-DS40002345A.pdf#_OPENTOPIC_TOC_PROCESSING_d5209e60328
        TCA0.SINGLE.PER = 100;
        TCA0.SINGLE.CTRLA |= 0b00001111;
        TCA0.SINGLE.CMP0 = 1041;
        TCA0.SINGLE.INTCTRL = 0b00010000;
    }
}


void loop(void) {
    static uint8_t x = 0;
    static uint8_t y = 0;
    
    matrix::set(x, y);
    delay(10);

    matrix::unset(x, y);
    x = (x < 15) ? x + 1 : 0;
    y = (y < 15) ? y + 1 : 0;
}
