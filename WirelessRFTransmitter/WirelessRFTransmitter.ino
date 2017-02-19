#include <Button.h>
#include <RH_ASK.h>

uint8_t ledStatus = false;
const char* ON_MESSAGE = new char[1]{0x55}; //binary 0101 0101
const char* OFF_MESSAGE = new char[1]{0x96}; //binary 1001 0110

//setup the driver as such:
// speed: 2400 bits per second
// rxPin - receiving pin: 11 --not used for this transmitting script
// txPin - transmitting pin: 12
// pttPin - transmitting enable pin: 10 --not used for this transmitting script. 
//    RadioHead can enable the transmitter only when transmitting data
//    but this is not supported on the SYN115 breakout board
// pttInverted: true - LOW signal will enable the tranmitter if set to true. Since we don't control the transmitter
//    we want this value to be true
RH_ASK driver(2400, 11, 12, 10, true);

//Uses idyl.io Button library. Feel free to replace it by raw reading or your own version
Button button(8, INPUT_PULLUP, true);

void setup() {
  //initialize wireless driver
  driver.init();
}

void loop() {

  button.poll();

  if(button.rising()){
    ledStatus = !ledStatus; //turn LED on or off

    if(ledStatus){
      driver.send((uint8_t *)ON_MESSAGE, 1); //send one byte. To send a whole message you can use strlen(MESSAGE)
    }
    else{
      driver.send((uint8_t *)OFF_MESSAGE, 1); //send one byte
    }
    driver.waitPacketSent();
  }

}
