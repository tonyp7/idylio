/*
Example code implementing the ExponentialWaveLed function.
Works on an STM32F103 'blue pill' board.

Also implements a LED 'chaser' of 8 leds on 8 GPIO's
And demonstrates how to 'multitask' the 'wave' and
'chase' functions
*/

#include "ExponentialWaveLed.h"

/*Here's where we define which of the pins our 'chaser' LEDs are connected to*/
const int LEDS[8]={
  PB9,
  PB8,
  PB7,
  PB6,
  PB5,
  PB4,
  PB3,
  PA15
};

#define WHITELED A0  // this is the LED we'll be 'waving'

ExponentialWaveLed exponentialWaveLed;
const unsigned long WAVE_LEN = 2000UL;  //2 second 'wave' time
unsigned long milli = 0UL;

// the setup function runs once when you press reset or power the board
void setup() {
/*init all of our LED pins as outputs, and set them all LOW (they don't all start our in  
 * the same state otherwise */
  for(int i=0; i<=7; i++){
    pinMode(LEDS[i],OUTPUT);
    digitalWrite(LEDS[i],LOW);
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH); 
  
  //initialize our wave routine
  exponentialWaveLed.setup(WHITELED, WAVE_LEN);

//  Serial.begin(115200);
}

void loop() { 
  for(int i=0; i<=7; i++){    // loop through each of our chaser segment LED's
    digitalWrite(LEDS[i],!digitalRead(LEDS[i]));
    for(int j=0; j<=19; j++){  //How long do we keep our 'chaser' segment lit
      delay(1);
      exponentialWaveLed.update(millis()); //keep on updating our wave LED 
    }
    digitalWrite(LEDS[i],!digitalRead(LEDS[i]));
    for(int j=0; j<=19; j++){ // how long do we keep our 'chaser' segment 'off' for
      delay(1);
      exponentialWaveLed.update(millis());
    }
  }
 
}
