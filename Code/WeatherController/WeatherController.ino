#include <Wire.h>
#include <avr/power.h>
#include "EnableInterrupt.h"
#include "LowPower.h"
#include "Controller.h"
#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"

const int DHTPIN = 4;
const int knockPin = 11;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);
VarSpeedServo servo;
InfineonRGB led;
Blinker blinker(0x0777,1);

CONTROLLER Controller(&dht,&servo,&led,&Serial1,&blinker);

void setup() {
  power_adc_disable();          //Not using any analogue functionality so can turn it off
  Serial.begin(115200);
  while (!Serial) {
     ; // wait for serial port to connect.
   }
  
  Serial1.begin(115200);
  Controller.begin();
  enableInterrupt(knockPin, knock, CHANGE);
}

void loop() {
  Controller.run();
}

void knock() {
  Controller.wake();
}
