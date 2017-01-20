/*
  QuadraticWaveLed
  Pulses a LED according to a sine wave, with the periodicity given as argument.

  The pins output used for these must be PWM pins.

  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 20 January 2017
  by Tony Pottier
  
*/

#include "QuadraticWaveLed.h"

QuadraticWaveLed quadraticWaveLed;
const int LED_PIN = 11;     //11 is a PWM pin on the Arduino Uno. Change to whichever pin you wish to use.
const unsigned long WAVE_LEN = 2000UL;  //in milliseconds. This wave will last 2 seconds.

unsigned long milli = 0UL;

void setup() {
  quadraticWaveLed.setup(LED_PIN, WAVE_LEN);
}

void loop() {
  milli = millis();
  quadraticWaveLed.update(milli);
}
