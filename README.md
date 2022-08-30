# ProtoPCB

Business card PCB and pocket Attiny3227 and LED matrix playground. Powered by a CR2032 battery
<p align="middle">
  <img src="https://github.com/Lmello1/ProtoPCB/blob/main/PCB%20rev%202.0/Photos/PCB_Front.JPG"/>
  <img src="https://github.com/Lmello1/ProtoPCB/blob/main/PCB%20rev%202.0/Photos/PCB_Back_top.jpg"/>
</p>

## Description

A business card PCB based on the ATTINY3227 chipset. Using 4 74HC595D shift registers to drive a 256 LED matrix. With a standard UDPI interface and 3 input buttons the possibilities are endless.
The current code includes various games and demo programs. Please feel free to make your own and share!

NOTE: Shift register U3 is reversed for easier routing.

## Current programs
* Snake

## Coming soon
* Pong
* Tic Tac Toe
* Tetris

## LED matrix info
```
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
X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X |---- U3---V--(REVERSED)
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
```


## PCB Revision History
* Rev 1.0 - 1st working version (Do not recreate-one shorted track) NOTE: Removed from github

* Rev 2.0 - Vertical PCB format and visual improvements. Changed foorptints for shift registers

* Rev 3.0 - CR2032 battery holder added for the back, Track routing improvements

## Creators

Landon Mello
[@Landon_Mello](https://twitter.com/Landon_Mello_)

Ben Liebmann
