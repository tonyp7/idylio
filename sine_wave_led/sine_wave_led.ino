/*
  sine_wave_led
  Pulses a LED according to a sine wave, with the periodicity given as argument.

  The pins output used for these must be PWM pins.

  Please see https://idyl.io for complete tutorial on how this works.
  
  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 10 January 2017
  by Tony Pottier
  
*/

const int LED_PIN_A = 0;
const int LED_PIN_B = 1;
unsigned long milli = 0UL;


void sin_pwm(const int pin_number, const unsigned long timer, const unsigned int len){
    //get the timer in the [0 ; len] range
    unsigned long mod = timer % len;
    
    //function used: 0.5 * (1 + sin(2*pi*x - pi/2))
    float f = 0.5f * (1.0f + sin(2.0f * PI * (mod/(float)len) - PI * 0.5f));
    analogWrite(pin_number, (unsigned uint8_t) (f * 255.0f));
}

void setup() {
  pinMode(LED_PIN_A, OUTPUT);
  pinMode(LED_PIN_B, OUTPUT);
}

void loop() {
  milli = millis();
  sin_pwm(LED_PIN_A, milli, 1000UL);
  sin_pwm(LED_PIN_B, milli, 500UL);
}
