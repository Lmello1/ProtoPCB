#include "matrix.hpp"

#include <Arduino.h>
#include <util/atomic.h>

volatile matrix::rowmask_t matrix::screen_buf[32] = {0};

#define L "\n\t"
#define PULSE_CLOCK "\n\tsbi 0x9, 1\n\tcbi 0x9, 1"
#define BANGBIT(n) "\n\tsbrc r21, " #n "\n\tsbi 0x5, 2\n\tsbrs r21, " #n "\n\tcbi 0x5, 2" PULSE_CLOCK

/** 
 * \brief Interrupt triggered by timer b that is used to display the LED matrix row by row
 */
ISR(TCA0_CMP0_vect) {
    static uint8_t row = 0;
    //Increment the currently displayed row or reset to the first row if we have displayed the last one
    row = (row >= 16) ? 0 : row + 1;
    //Get the address of the lower byte of the screen buffer
    matrix::rowmask_t *screen_buf_offset = (matrix::rowmask_t *)(matrix::screen_buf + (row << 1));
    asm volatile(
        "cbi 0x9, 0"              //Set the latch pin low
        L "mov r21, %0"           //Move the row count to the counter register
        L "cpi r21, 8"            //Check if the row is greater than 7
        L "brlo lt_8"             //Write row bits for rows below or equal to 7
        
        L "gt_8:"
            L "subi r21, 8"
            L "ldi r22, 7"      //Assign 7 to r22 in order to traverse the column bits MSB first

            L "sbi 0x5, 2"     //Drive the data pin high
            PULSE_CLOCK        //Pulse the clock pin 8 times (manually unrolled loop)
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            
            L "cln"                            //Clear the negative (underflow) flag, as it is used later for control flow
            L "gt_8_loop:"
                L "brbs 2, cols"               //If the reverse counter has underflowed, continue to writing column data
                L "cp r22, r21"                //Check if r22 is equal to the counter
                L "breq gt_8_loop_z"           
                    PULSE_CLOCK                //If r22 is not equal to the current row, write a 1 to the column bits
                    L "jmp gt_8_loop_after"
                L "gt_8_loop_z:"               //If r22 is equal to the counter, write a 0 to the column bits
                    L "cbi 0x5, 2"
                    PULSE_CLOCK
                    L "sbi 0x5, 2"
                L "gt_8_loop_after:"
                L "dec r22"                    //Decrement the reverse counter
                L "jmp gt_8_loop"              //Repeat the loop
                
        L "lt_8:"
            L "clr r22"                   //Zero out the value of r22 to prepare a counter
            L "sbi 0x5, 2"                //Set the data pin high
            L "lt_8_loop:"
                L "cpi r22, 8"            //Check if we have iterated through the lower bits
                L "breq lt_8_ones"
                
                L "cp r21, r22"           //Compare the counter with the row value
                L "breq lt_8_loop_z"      //If the counter is not equal to the current row, write a 1 to the shift register
                    PULSE_CLOCK           //Pulse the clock pin
                    L "jmp lt_8_loop_after"
                L "lt_8_loop_z:"          //If the counter is equal to the current row, write a 0 to the shift register
                    L "cbi 0x5, 2"        //Drive the data pin low
                    PULSE_CLOCK           //Pulse the clock pin
                    L "sbi 0x5, 2"        //Drive the data pin back high
                L "lt_8_loop_after:"
                
                L "inc r22"               //Increment the counter value
                L "jmp lt_8_loop"
            
            L "lt_8_ones:"
            PULSE_CLOCK    //Pulse the clock pin 8 times (manually unrolled loop)
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
            PULSE_CLOCK
        L "cols:"
            L "ldd r21, %a1+1"        //Load the second byte into r21
            L "bitbanging:"
            BANGBIT(7)
            BANGBIT(6)
            BANGBIT(5)
            BANGBIT(4)
            BANGBIT(3)
            BANGBIT(2)
            BANGBIT(1)
            BANGBIT(0)
            L "brts end"           //If this is the second run, exit
            L "ld r21, %a1"        //Load the first byte into r21
            L "set"                //Set the T bit in the status register to mark this as the second iteration
            L "jmp bitbanging"
        L "end:"
        L "sbi 0x9, 0"             //Drive the latch pin low
        :
        : "r" (row), "b" (screen_buf_offset)
        : "r21", "r22"
    );
}

#undef L
