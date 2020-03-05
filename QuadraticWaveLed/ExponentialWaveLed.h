/*
  ExponentialWaveLed.h
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

typedef int16_t f7p9;
typedef uint32_t uf16p16;

//signed 7 bit integer / 9 bit decimal
#define inttof7p9(n)          ((n) << 9)
#define f7p9toint(n)          ((n) >> 9)
#define floattof7p9(n)        ((int16_t)((n) * (1 << 9))) 
#define f7p9tofloat(n)        (((float)(n)) / (float)(1<<9))

//signed 23 bit integer / 9 bit decimal
#define floattof23p9(n)     ((int32_t)((n) * ((int32_t)1 << 9))) 
#define f23p9tofloat(n)     (((float)(n)) / (float)(1<<9))

//unsigned 16 bit integer / 16 bit decimal
#define floattouf16p16(n)        ((uf16p16)((n) * ((uf16p16)1 << 16))) 
#define inttouf16p16(n)          (((uf16p16)n) << 16)
#define uf16p16tofloat(n)        (((float)(n)) / (float)((uf16p16)1<<16))


//return a f7p9 of a multiplication of two f16p16. If the number doesn't fit it will be truncated
static inline f7p9 muluf16p16(uf16p16 a, uf16p16 b) {
	return  (f7p9)(((uf16p16)a * (uf16p16)b) >> (16+7));
}

//Simple multiplication of two f7p9 terms. Operation is done on 32 bits to avoid overflow.
static inline f7p9 mulf7p9(f7p9 a, f7p9 b){
	return  (f7p9)  (  (( (int32_t)a * (int32_t)b) >> 9) );
}

class ExponentialWaveLed{
	private:
	f7p9 exponentialWavef7p9(f7p9 x);
	f7p9 value;
	int pinNo;
	unsigned long waveLen;
	uf16p16 inverseWaveLen;
	
	public:
	void setup(const int pinNumber, const unsigned long waveDuration);
	void update(const unsigned long milli);
};

