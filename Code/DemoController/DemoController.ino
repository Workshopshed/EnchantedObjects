#include <Process.h>
#include <Wire.h>
#include "Controller.h"
#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"

int const DHTPIN = 4;
#define DHTTYPE DHT22   // DHT 22  (AM2302)

DHT dht(DHTPIN, DHTTYPE);
VarSpeedServo servo;
InfineonRGB led;
CONTROLLER Controller(&dht,&servo,&led);

void setup() {
  Serial.begin(9600); 
  Serial.println("System test!");
  Controller.begin();
}

void loop() {
  Controller.run();
  delay(10000);
}
