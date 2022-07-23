// ST_CP pin 12
const int latchPin = 12;
// SH_CP pin 11
const int clockPin = 13;
// DS pin 14
const int dataPin = 9;


void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
 
void loop() {
  // Count from 0 to 255 and display in binary
 
  for (int numberToDisplay = 0; numberToDisplay < 256; numberToDisplay++) {
 
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW); 
 
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
 
    // ST_CP HIGH change LEDs
    digitalWrite(latchPin, HIGH);
 
    delay(500);
  }
}
