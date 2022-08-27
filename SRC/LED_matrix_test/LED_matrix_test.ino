#define SNAKE
#include "game.hpp"
#include "matrix.hpp"
#include <Arduino.h>
#include <util/atomic.h>

static constexpr uint8_t BUTTON_1 = 15;
static constexpr uint8_t BUTTON_2 = 16;
static constexpr uint8_t BUTTON_3 = 17;


void setup(void) {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_3, INPUT_PULLUP);
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        //https://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny3224-3226-3227-Data-Sheet-DS40002345A.pdf#_OPENTOPIC_TOC_PROCESSING_d5209e60328
        TCA0.SINGLE.CTRLA |= 0b00001111;
        TCA0.SINGLE.CMP0 = 1041;
        TCA0.SINGLE.INTCTRL = 0b00010000;
    }

    play();
}

static uint8_t x = 0, y = 0;
