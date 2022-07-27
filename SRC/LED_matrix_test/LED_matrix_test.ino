const int latchPin = 12;
const int clockPin = 13;
const int dataPin = 9;
const int Button1 = 15;
const int Button2 = 16;
const int Button3 = 17;


 
void setup ()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
}
void loop()  {
    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);
  
    digitalWrite(latchPin, HIGH);
 
    delay(250);

    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);
  
    digitalWrite(latchPin, HIGH);
 
    delay(250);

    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B01010101);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    digitalWrite(latchPin, HIGH);
 
    delay(250);

    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    shiftOut(dataPin, clockPin, MSBFIRST, B10101010);

    digitalWrite(latchPin, HIGH);
 
    delay(250);

    digitalWrite(latchPin, LOW);
 
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);

    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);

    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);

    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);

    digitalWrite(latchPin, HIGH);
}