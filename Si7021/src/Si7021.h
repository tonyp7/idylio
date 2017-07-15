/*
  Si7021.h
  Very simple class to interface to a Si7021 temperature and humidity sensor.

  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  modified 15th July 2017
  by Tony Pottier
  https://idyl.io
  
*/


//these values are coming directly from the documentation
//The timeout is set to 
#define SI7021_ADDRESS 0x40
#define SI7021_MEASURE_HUMIDIY_HOLD_MASTER_MODE 0xE5
#define SI7021_MEASURE_HUMIDIY_NO_HOLD_MASTER_MODE 0xF5
#define SI7021_MEASURE_TEMPERATURE_HOLD_MASTER_MODE 0xE3
#define SI7021_MEASURE_TEMPERATURE_NO_HOLD_MASTER_MODE 0xF3
#define SI7021_READ_TEMPERATURE_FROM_PREVIOUS_RH_MEASUREMENT 0xE0
#define SI7021_RESET 0xFE
#define SI7021_WRITE_REGISTER 0xE6
#define SI7021_READ_REGISTER 0xE7

//maximum wait time is for 3 bytes. At a 100 Khz I2C bus, 50ms is a safe value for timeout
//eg: 100 bit per ms, 12.5 byte per ms, 37.5ms to transfer 3 bytes
#define SI7021_READ_TIMEOUT (uint8_t)50

//Read Electronic ID 1st Byte 0xFA 0x0F 
//Read Electronic ID 2nd Byte 0xFC 0xC9 
//Read Firmware Revision 0x84 0xB8



class Si7021
{
	private:
		uint16_t readSensor(const uint8_t instr, const int8_t returnSize);
	public:
		Si7021();
		void begin();
		void reset();
		float measureTemperature();
		float getTemperatureFromPreviousHumidityMeasurement();
		float measureHumidity();
		float measureTemperatureF();
		float getTemperatureFromPreviousHumidityMeasurementF();
		float measureHumidityF();
		uint64_t getSerialNumber();
};
