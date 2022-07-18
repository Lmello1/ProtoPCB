# ProtoPCB

Business card PCB and pocket Attiny3227 and LED matrix playground

## Description

A business card PCB based on the ATTINY3227 chipset. Using 4 74HC595D shift registers to drive a 256 LED matrix. With a standard UDPI interface and 3 input buttons the possibilities are endless 

## LED matrix info

                 led matrix data flow
attiny3227
V
\_________>_______________________>______________________
         U1                      U2                      \
 ____________________    ____________________             |
/                    \  /                    \            |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X \          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |---- U3   V
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X /          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X \          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |---- U4   V
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |          |
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X /          *


## Creators

Landon Mello
[@Landon_Mello](https://twitter.com/Landon_Mello_)
