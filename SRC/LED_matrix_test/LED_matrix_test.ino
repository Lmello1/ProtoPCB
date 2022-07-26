#include <Arduino.h>


static constexpr uint8_t LATCH_PIN = 12;
static constexpr uint8_t CLOCK_PIN = 13;
static constexpr uint8_t DATA_PIN = 9;


void setup(void) {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
}


void loop(void) {
    digitalWrite(LATCH_PIN, LOW);

    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B10101010);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B10101010);
    digitalWrite(LATCH_PIN, HIGH);

    delay(500);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0b101010101);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B01010101);
    digitalWrite(LATCH_PIN, HIGH);

    delay(500);
}


