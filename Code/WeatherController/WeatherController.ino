#include <Process.h>
#include <Wire.h>
#include "EnableInterrupt.h"
#include "LowPower.h"
#include "Controller.h"
#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"

const int DHTPIN = 4;
const int knockPin = 12;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);
VarSpeedServo servo;
InfineonRGB led;
CONTROLLER Controller(&dht,&servo,&led);

void setup() {
  Serial.begin(9600); 
  Serial.println("System test!");
  Controller.begin();
  enableInterrupt(knockPin, knock, CHANGE);
}

void loop() {
  Controller.run();
  delay(1000);
}

void knock() {
  Controller.wake();
}
