#include "Controller.h"

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led){
  _dht = dht;
  _servo = servo;
  _led = led;
  pinMode(A5, OUTPUT);
  pinMode(powerpin, OUTPUT);
  //Todo: Add in the handshake pin
}

void CONTROLLER::begin() {
    position = 3; // Middle position
    
    powerOn();
    lininoOn();
    
    //Todo: Setup serial port
}

void CONTROLLER::run(void) {
    readLocalWeather();
    readNetWeather();
    // Move servo
    // Turn on Light
}

void CONTROLLER::readLocalWeather() {
  // Todo: Check DHT
};

void CONTROLLER::readNetWeather() {
  // Todo: Read internet weather
  // Request weather, pass in the local conditions
  
  // Read weather over /dev/ttyATH0<->Serial1
  // String weather = Serial1.readStringUntil('\n');
  
  String weather = "OK!,Cloudy,3,19.00"; //Check,Status,Position,Temperature
  if (!weather.startsWith("OK!")) { return; }  //Todo: Handle case where using local values
  if (!parseWeather(weather)) { return; } // No change in weather


}

bool CONTROLLER::parseWeather(String weather) {
  bool changed = false;
  
  const char separator = ',';
  int c1 = weather.indexOf(separator);
  int c2 = weather.indexOf(separator, c1+1);
  int c3 = weather.indexOf(separator, c2+1);
  // Check if we have 4 values separated with commas
  if (c1 == -1 || c2 == -1 || c3 == -1) { return changed; }

  String sPos = weather.substring(c2+1,c3);
  int tempPos = sPos.toInt();
  if (tempPos != 0) {
    if (tempPos != position) {
      changed = true;
      position = tempPos;
    }
  }

  String sTemp = weather.substring(c3);
  float tempTemp = sTemp.toFloat();
  if (tempTemp != 0) {
    if (nettemp != tempTemp) {
      changed = true;
      nettemp = tempTemp;
    }
  }
  
  return changed;
}


void CONTROLLER::powerOn() {
  digitalWrite(powerpin, HIGH);    // sets the MOSFET on
}

void CONTROLLER::powerOff() {
  digitalWrite(powerpin, LOW);    // sets the MOSFET off
}

void CONTROLLER::lininoOn() {
  digitalWrite(A5, LOW);    // sets the Linino off
}

void CONTROLLER::lininoOff() {
  digitalWrite(A5, HIGH);    // sets the Linino on
}

bool CONTROLLER::lininoRunning() {
  // Todo: Is Linino running yet?
  // See https://gist.github.com/wayoda/db3c023417757f726088
  
}

void CONTROLLER::moveServo() {
  // Move servo to correct position
}

void CONTROLLER::setLED() {
  // Change Light to correct colour
}

void CONTROLLER::sleep() {
  // Sleep the ATMega
}
