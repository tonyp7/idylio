#include "ExponentialWaveLed.h"
  
/*Here's where we define which of the pin number our LEDs are connected to*/
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

#define WHITELED A0

ExponentialWaveLed exponentialWaveLed;
const unsigned long WAVE_LEN = 2000UL;
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
  exponentialWaveLed.setup(WHITELED, WAVE_LEN);

//  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() { 
  for(int i=0; i<=7; i++){    
    digitalWrite(LEDS[i],!digitalRead(LEDS[i]));
    for(int j=0; j<=19; j++){
      delay(1);
      exponentialWaveLed.update(millis());
    }
    digitalWrite(LEDS[i],!digitalRead(LEDS[i]));
    for(int j=0; j<=19; j++){
      delay(1);
      exponentialWaveLed.update(millis());
    }
  }
 
}
