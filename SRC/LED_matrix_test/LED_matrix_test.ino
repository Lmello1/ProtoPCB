const int latchPin = 12;
const int clockPin = 13;
const int dataPin = 9;



 
void setup ()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
void loop()
{
    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);
  
    digitalWrite(latchPin, HIGH);
 
    delay(500);

    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);
  
    digitalWrite(latchPin, HIGH);
 
    delay(500);
}