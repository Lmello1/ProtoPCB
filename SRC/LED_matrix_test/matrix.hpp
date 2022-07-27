#pragma once
#include <stdint.h>

static constexpr uint8_t LATCH_PIN = 12;
static constexpr uint8_t CLOCK_PIN = 13;
static constexpr uint8_t DATA_PIN = 9;

namespace matrix {

/** \brief Constant passed to the `set` function to turn an LED on, so we can eliminate an unneeded bitshift */
static constexpr uint8_t LED_ON = 0b10000000;

/** 
 * How a half of a single row of the LED matrix is stored,
 * here every bit in the number indicates if the LED should be on or off
 */
using rowmask_t = uint8_t;

/** 
 * \brief Buffer containing bitmasks for each row in the matrix display.
 * The reason that 32 uint8_ts are stored instead of 16 uint16_ts is because operations on uint8_ts are atomic,
 * meaning they cannot be interrupted by the screen rendering interrupt. So, we can modify portions of the display buffer without needing an `ATOMIC_BLOCK`
 */
extern volatile rowmask_t screen_buf[32];

/**
 * Set an LED in the matrix display by (x, y) coordinates
 */
__attribute__((always_inline))
inline void set(uint8_t x, uint8_t y) {
    uint8_t i = y * 2 + (x > 3 ? 1 : 0);
    screen_buf[i] |= (LED_ON >> x);
}

/**
 * Set or unset an LED in the matrix display by (x, y) coordinates
 */
__attribute__((always_inline))
inline void unset(uint8_t x, uint8_t y) {
    uint8_t i = y * 2 + (x > 3 ? 1 : 0);
    screen_buf[i] &= ~(LED_ON >> x);
}

/**
 * Set the contents of an entire row to the bitmask specified. Note that this function is **not** atomic and
 * must be surrounded by an `ATOMIC_BLOCK` to ensure no garbled screen data is present
 * \param row The row index from 0-15 inclusive
 * \param val Bitmap of LED values, e.x.: 0b0101010101010101
 */
__attribute__((always_inline))
inline void setrow(uint8_t row, uint16_t val) {
    screen_buf[row * 2 + 1] = (uint8_t)val;
    screen_buf[row * 2] = (uint8_t)(val >> 8);
}

}
