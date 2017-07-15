/*
  Si7021.cpp
  Very simple class to interface to a Si7021 temperature and humidity sensor.

  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 15th July 2017
  by Tony Pottier
  https://idyl.io
  
*/

#include <stdint.h>
#include <arduino.h>
#include <Wire.h>
#include "Si7021.h"

Si7021::Si7021(){};

void Si7021::begin(){
  //init Arduino I2C lib
  Wire.begin();
}


/// <summary>Write a specific instruction to the sensor and return the result</summary>
/// <param name="instr">The instruction</param>
/// <param name="returnSize">Number of bytes expected. Due to Arduino library being retarded this must be a signed int</param>  
/// <returns>Read result</returns>
uint16_t Si7021::readSensor(const uint8_t instr, const int8_t returnSize){
	
	//timeout counter
	uint8_t timeout = 0;
	
	//send the instruction
	Wire.beginTransmission(SI7021_ADDRESS);
	Wire.write(instr);
	Wire.endTransmission();
	
	//according to the spreadsheet the longest time to wait is 14bit resolution humidity + temp, which is 12 + 10.8ms.
	//25 is therefore a safe value for all instructions
	delay(25);
	
	//wait for data to be ready
	Wire.requestFrom(SI7021_ADDRESS, returnSize);
	while (Wire.available() < returnSize){
		delay(1);
		timeout++;
		if(timeout > SI7021_READ_TIMEOUT){
			//later down we force the last 2 bit to be 0.
			//Therefore 1 is not a possible value and can be caught as an error if needed
			return 1;
		}
	}
	
	uint16_t msb = Wire.read();
	uint8_t lsb = Wire.read();
	
	if(returnSize >= 3){
		Wire.read(); //third byte is the checksum
	}
	
	//a humidity measurement will always return XXXXXX10 in the LSB field.
	//Clear the last 2 bits of lsb. Little quirk of the sensor!
	lsb &= 0xFC;
	
	return (uint16_t)((msb << 8) | lsb);
}


/// <summary>
///		Measure the temperature. Since reading humidity also forces a temperature measurement, you shouldn't use this function unless you just want the temperature
/// 	<seealso cref="Si7021::getTemperatureFromPreviousHumidityMeasurement"/>  
/// </summary>
/// <returns>Temperature, in Celcius</returns>
float Si7021::measureTemperature(){
	uint16_t dword = readSensor(SI7021_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE, (uint8_t)3);
	return 175.25f * dword / 65536.0f - 46.85f;
}

/// <summary>
///		Measure the temperature. Since reading humidity also forces a temperature measurement, you shouldn't use this function unless you just want the temperature
/// 	<seealso cref="Si7021::getTemperatureFromPreviousHumidityMeasurementF"/>  
/// </summary>
/// <returns>Temperature, in Fahrenheit </returns>
float Si7021::measureTemperatureF(){
	return this->measureTemperature() * 1.8f + 32.0f;
}

/// <summary>
///		Measure the humidy.
/// </summary>
/// <returns>Relative Humidity, in percent</returns>
float Si7021::measureHumidity(){
	uint16_t dword = readSensor(SI7021_MEASURE_HUMIDIY_NO_HOLD_MASTER_MODE, (uint8_t)3);
	return 125.0f * dword / 65536.0f - 6.0f;
}


/// <summary>
///		Each time a relative humidity measurement is made a temperature measurement is also made for the purposes of
///		temperature compensation of the relative humidity measurement. If the temperature value is required, it can be
///		read using this function; this avoids having to perform a second temperature measurement. 
/// </summary>
/// <returns>Temperature, in Celcius</returns>
float Si7021::getTemperatureFromPreviousHumidityMeasurement(){
	uint16_t dword = readSensor(SI7021_READ_TEMPERATURE_FROM_PREVIOUS_RH_MEASUREMENT, (uint8_t)2);
	return 175.25f * dword / 65536.0f - 46.85f;
}

/// <summary>
///		Each time a relative humidity measurement is made a temperature measurement is also made for the purposes of
///		temperature compensation of the relative humidity measurement. If the temperature value is required, it can be
///		read using this function; this avoids having to perform a second temperature measurement. 
/// </summary>
/// <returns>Temperature, in Fahrenheit</returns>
float Si7021::getTemperatureFromPreviousHumidityMeasurementF(){
	return getTemperatureFromPreviousHumidityMeasurementF() * 1.8f + 32.0f;
}

/// <summary>
///		Soft reset of the chip.
/// </summary>
void Si7021::reset(){
	Wire.beginTransmission(SI7021_ADDRESS);
	Wire.write(SI7021_RESET);
	Wire.endTransmission();
	delay(15); //datasheet specifies device takes up to 15ms (5ms typical) before going back live
}

/// <summary>
///		Read the 64 bit serial number of the Si7021 sensor
///		Because 64 bit 
/// </summary>
/// <returns>Serial number</returns>
uint64_t Si7021::getSerialNumber(){
	
	uint64_t serialNo = 0ULL;
	uint8_t buffer = 0x00;

	
	Wire.beginTransmission(SI7021_ADDRESS);
	Wire.write(0xFA);
	Wire.write(0X0F);
	Wire.endTransmission();

	//4 byte + CRC for each
	Wire.requestFrom(SI7021_ADDRESS, 8);
	while (Wire.available() >= 2){
		buffer = Wire.read();
		serialNo = (serialNo << 8) | buffer;
		Wire.read(); //discard checksum
	}
	
	Wire.beginTransmission(SI7021_ADDRESS);
	Wire.write(0xFC);
	Wire.write(0xC9);
	Wire.endTransmission();

	//4 byte + CRC for each
	Wire.requestFrom(SI7021_ADDRESS, 8);
	while (Wire.available() >= 2){
		buffer = Wire.read();
		serialNo = (serialNo << 8) | buffer;
		Wire.read(); //discard checksum
	}
	
	return serialNo;
	
}
