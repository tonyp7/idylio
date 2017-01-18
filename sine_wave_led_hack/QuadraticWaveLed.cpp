/*
  QuadraticWaveLed.cpp
  Pulses a LED according to a sine wave, with the periodicity given as argument.

  The pins output used for these must be PWM pins.

  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 18 January 2017
  by Tony Pottier
  
*/

#include "stdint.h"
#include "arduino.h"
#include "QuadraticWaveLed.h"


//Apply the following function:
// f(x) = x^2 if x <= 1
// f(x) = (x-2)^2 + 2 if 1 < x <= 3
// f(x) = (x-4)^2 otherwise
// this function is almost a perfect sine wave on the [0;4] range.
f7p9 QuadraticWaveLed::quadraticWavef7p9(f7p9 x) {
  if (x <= inttof7p9(1)) {
    return mulf7p9(x, x);
  }
  else if (x <= inttof7p9(3)) {
    x -= inttof7p9(2);
    x = mulf7p9(x, x);
    x = inttof7p9(0) - x + inttof7p9(2);
    return x;
  }
  else {
    x -= inttof7p9(4);
    return mulf7p9(x, x);
  }
}

void QuadraticWaveLed::setup(const int pinNumber, const unsigned long waveDuration){
	this->pinNo = pinNumber;
	this->waveLen = waveDuration;
	this->inverseWaveLen = floattouf16p16(1.0f / waveDuration);
	pinMode(pinNumber, OUTPUT);
}

void QuadraticWaveLed::update(const unsigned long milli){
	unsigned long mod = milli % this->waveLen;

	//transform to 0--1 range
	this->value = muluf16p16(inttouf16p16(mod), this->inverseWaveLen);

	//convert to 0--4 range: multiply by 4 by shifting left twice
	this->value = this->value << 2; 

	//apply wave
	this->value = quadraticWavef7p9(this->value);

	//convert to 0-255 range
	uint8_t pwm_value = ((int32_t)this->value * floattof23p9(127.5f)) >> 18;

	//write to LED
	analogWrite(this->pinNo, pwm_value);

}