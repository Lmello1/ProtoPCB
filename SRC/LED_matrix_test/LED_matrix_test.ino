#include <Arduino.h>

static constexpr uint8_t LATCH_PIN = 12;
static constexpr uint8_t CLOCK_PIN = 13;
static constexpr uint8_t DATA_PIN = 9;

static constexpr uint8_t LED_ON = 0b10000000;

/** 
 * How a single row of the LED matrix is stored,
 * here every bit in the number indicates if the LED should be on or off
 */
using rowmask_t = uint16_t;

/** \brief How long to wait in milliseconds before displaying the next matrix row */
static constexpr uint8_t ROW_DELAY = 33;

/** 
 * \brief Buffer containing bitmasks for each row in the matrix display
 */
static rowmask_t matrix_buf[16] = {0};

void setup(void) {
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    TCCR1A = TCCR1B = TCNT1 = OCR1A = 0;
    //Enable Counter mode for the timer, counting to the specified value before interrupt
    TCCR1A |= _BV(WGM01);
    //Set the clock to be the CPU frequency / 1024
    TCCR1B |= _BV(CS02) | _BV(CS00);
    //Interrupt when timer reaches the value in OCRA register
    TIMSK1 |= _BV(OCIE0A);
    //Count to 255 before triggering interrupt
    OCR1A = 255;
}


void loop(void) {
    digitalWrite(LATCH_PIN, LOW);
    
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B10101010);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B10101010);
    digitalWrite(LATCH_PIN, HIGH);
    
    delay(500);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B01010101);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, B01010101);
    digitalWrite(LATCH_PIN, HIGH);

    delay(500);
}

/**
 * Set or unset an LED in the matrix display by (x, y) coordinates
 */
inline void set(uint8_t x, uint8_t y, uint8_t set) {
    matrix_buf[y] = (matrix_buf[y] & ~(LED_ON >> x)) | (matrix_buf[y] | (set >> x));
}

/**
 * Write the data contained in `matrix_buf` to the LED matrix
 */
void render(void) {
    for(uint8_t i = 0; i < 16; ++i) {
        
    }
}

/** 
 * \brief Interrupt triggered by timer1 that is used to display the LED matrix row by row
 */
SIGNAL(TIMER1_COMPA_vect) {
    static uint8_t row = 0;
    //Increment the currently displayed row or reset to the first row if we have displayed the last one
    row = (row >= 16) ? 0 : row + 1;
    uint16_t rowbits = 1 << row;
    digitalWrite(LATCH_PIN, LOW);
    //write lower 8 row bits to U4
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(rowbits));
    //write upper 8 row bits to U3
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(rowbits >> 8));

    //write lower 8 column bits to U2
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(matrix_buf[row]));
    //write upper 8 column bits to U1
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, (uint8_t)(matrix_buf[row] >> 8));

    digitalWrite(LATCH_PIN, HIGH);
}
