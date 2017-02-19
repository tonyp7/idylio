/* 
  NixieCount

  Control a single nixie tube through a SN74141 nixie driver chip.
  This code will loop all nixie numbers from 0 to 9.

  This code is part of a complete tutorial on nixie tubes.
  Please see https://idyl.io for the complete picture.
 
  This example code is licensed under CC BY 4.0.
  https://creativecommons.org/licenses/by/4.0/

  modified 19 February 2017
  by Tony Pottier
*/

uint8_t currentValue = 0;


//Use pins 10, 11, 12 & 13 of Arduino
//Connect to pins A, B, C & D of your SN74141 Nixie driver chip
#define A 10
#define B 11
#define C 12
#define D 13

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  nixieWrite(A, B, C, D, 0);
}


void nixieWrite(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t value){
  //D is most significant bit
  //A is lead significant bit
  digitalWrite(d, (value & 0x08) >> 3);
  digitalWrite(c, (value & 0x04) >> 2);
  digitalWrite(b, (value & 0x02) >> 1);
  digitalWrite(a, value & 0x01);
}

void loop() {
  delay(1000);
  currentValue++;
  if(currentValue > 9) currentValue = 0;
  nixieWrite(A, B, C, D, currentValue);
}
