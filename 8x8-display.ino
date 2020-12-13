/*

8x8 LED Matrix

Data goes to PNP shift register first, then NPN shift register
Therefore, first transmitted byte gets shifted to the NPN shift register
and second byte will remain in the PNP shift register

PNP transistors connected to first shift register
NPN transistors connected to second shift register

PNP transistors (first shift register) defines the column
NPN transistors (second shift register) defines the row

 */

const int cycles_per_letter = 1000;  // Should do this based on millis?

//Latch pin (ST_CP)
const int latchPin = 12;
//Clock pin (SH_CP)
const int clockPin = 11;
////Data pin (DS)
const int dataPin = 10;

const int rows[8] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111,
};

const int S[8] = {
  B00111100,
  B01111110,
  B01100000,
  B01111100,
  B00111110,
  B00000110,
  B01111110,
  B00111100,
};

const int O[8] = {
  B00111100,
  B01111110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B00111100,
};

const int space[8] = {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

const int allOn[8] = {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
};

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  displayLetter(S);
  displayLetter(O);
  displayLetter(S);
  displayLetter(space);
  displayLetter(allOn);
  displayLetter(space);
}
  
void displayLetter(int letter[]){
  for(int cycle=0; cycle<cycles_per_letter; cycle++){
    for(int rowNum=0; rowNum<8; rowNum++){

      digitalWrite(latchPin, LOW);
      
      // shift the bits out:
      shiftOut(dataPin, clockPin, MSBFIRST, letter[rowNum]);
      shiftOut(dataPin, clockPin, MSBFIRST, rows[rowNum]);
      
      digitalWrite(latchPin, HIGH);
    }
  }
}
