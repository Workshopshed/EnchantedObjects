#include "Controller.h"

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led){
  _dht = dht;
  _servo = servo;
  _led = led;
  position = 3; // Middle position
}

void CONTROLLER::begin() {
    pinMode(LininoPin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    //Todo: Add in the handshake pin    

    
    //Todo: Setup serial port
}

void CONTROLLER::run(void) {
    //Todo: Determine if we want to sleep or stay awake
    lininoOn();
    powerOn();
    readLocalWeather();
    readNetWeather();
    moveServo();
    setLED();
    
    //Todo: Timeout and go to sleep
}

void CONTROLLER::readLocalWeather() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    localhumidity = _dht->readHumidity();
    localtemp = _dht->readTemperature();
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
    _servo->attach(servoPin);
    _dht->begin();                  //Todo: Check we can run these more than once
    _led->begin();
}

void CONTROLLER::powerOff() {
    _servo->stop();
    _servo->detach();
    digitalWrite(powerpin, LOW);    // sets the MOSFET off
}

void CONTROLLER::lininoOn() {
    digitalWrite(LininoPin, LOW);    // sets the Linino off
}

void CONTROLLER::lininoOff() {
    digitalWrite(LininoPin, HIGH);    // sets the Linino on
}

bool CONTROLLER::lininoRunning() {
  // Todo: Is Linino running yet?
  // See https://gist.github.com/wayoda/db3c023417757f726088
  
}

void CONTROLLER::moveServo() {
    int p = position;
    if (p == 0) { p = 3; }           // Default to middle position
    p = constrain(position, 1, 5);   // Ensure position valid
    int degrees = map(p,1,5,50,100); // Move servo to correct position 50 to 100 degrees
    _servo->write(degrees,10,false); // Slow move, don't wait
}

void CONTROLLER::setLED() {
  // Change Light to correct colour
}

void CONTROLLER::sleep() {
  // Sleep the ATMega
  // Need to check servo has finished moving before sleeping, perhaps put that into the run method rather than the sleep call
  
}
