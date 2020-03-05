/*
  ExponentialWaveLed.cpp
  Pulses a LED according to a sine wave, with the periodicity given as argument.

  The pins output used for these must be PWM pins.

  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 5 Mar 2020 by Brad Roy
    changed from a 'sine-esque' function
   	to an exponential one. It *looks* 
   	more linear
  
  Original code:
  18 January 2017
  by Tony Pottier
  
*/

#include "stdint.h"
#include "Arduino.h"
#include "ExponentialWaveLed.h"

//Apply the following function:
// f(x) = x^2 if x <= 1
// f(x) = (x-4)^2 otherwise
// this function has a period of '2,' and returns a value from 0 to 1.
f7p9 ExponentialWaveLed::exponentialWavef7p9(f7p9 x) {
  if (x <= inttof7p9(1)) {
	return mulf7p9(x, x);
  }
//  else if (x <= inttof7p9(3)) {
//    x -= inttof7p9(2);
//    x = mulf7p9(x, x);
//    x = inttof7p9(0) - x + inttof7p9(2);
//    return x;
//  }
  else {
    x -= inttof7p9(2);
    return mulf7p9(x, x);
  }
}

void ExponentialWaveLed::setup(const int pinNumber, const unsigned long waveDuration){
	this->pinNo = pinNumber;
	this->waveLen = waveDuration;
	this->inverseWaveLen = floattouf16p16(1.0f / waveDuration);
	pinMode(pinNumber, OUTPUT);
}

void ExponentialWaveLed::update(const unsigned long milli){
	unsigned long mod = milli % this->waveLen;

	//transform to 0--1 range
	this->value = muluf16p16(inttouf16p16(mod), this->inverseWaveLen);

	//convert to 0--4 range: multiply by 4 by shifting left twice
	this->value = this->value << 1; 

	//apply wave
	this->value = exponentialWavef7p9(this->value);

	//convert to 0-255 range
	uint8_t pwm_value = (((int32_t)this->value * floattof23p9(249.0f)) >> 18)+6;

	//write to LED
	analogWrite(this->pinNo, pwm_value);

}
