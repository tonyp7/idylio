#include "Si7021.h"

Si7021 si7021;


uint64_t serialNumber = 0ULL;

void setup() {
  Serial.begin(115200);
  si7021.begin();

  serialNumber = si7021.getSerialNumber();

  //arduino lib doesn't natively support printing 64bit numbers on the serial port
  //so it's done in 2 times
  Serial.print("Si7021 serial number: ");
  Serial.print((uint32_t)(serialNumber >> 32), HEX);
  Serial.println((uint32_t)(serialNumber), HEX);

}

void loop() {

  Serial.print("Humidity: ");
  Serial.print(si7021.measureHumidity());
  Serial.print("% - Temperature: ");
  Serial.print(si7021.getTemperatureFromPreviousHumidityMeasurement());
  Serial.println("C");
  delay(500);

  

}
