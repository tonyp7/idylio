#include <RH_ASK.h>


RH_ASK driver(2400, 11, 12, 10, true);

void setup()
{
    pinMode(8, OUTPUT);
    driver.init();
    Serial.begin(9600);

}
void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      Serial.println(buf[0]);
      
      if(buflen >= 1){
        if(buf[0] == 0x96){
          digitalWrite(8, LOW);
        }
        else if(buf[0] == 0x55){
          digitalWrite(8, HIGH);
        }
      }
    }
}
