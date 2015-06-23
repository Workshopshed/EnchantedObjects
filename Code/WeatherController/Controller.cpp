#include "Controller.h"

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial,Blinker *blinker){
  _dht = dht;
  _servo = servo;
  _led = led;
  _serial = serial;
  _blinker = blinker;
  position = 3; // Middle position
}

void CONTROLLER::begin() {
    pinMode(LininoPin, OUTPUT);
    pinMode(powerpin, OUTPUT);
    pinMode(HandshakePin, INPUT);
    pinMode(ButtonPowerPin, INPUT_PULLUP);
    pinMode(ButtonWifiPin, INPUT_PULLUP);
}

void CONTROLLER::run(void) {
    if (sleeps <= 0 || knock)
    {
        //Todo: Implement asynchronous request / read etc, perhaps a statemodel
          lininoOn();
          powerOn();
          readLocalWeather();
          requestNetWeather();
          readNetWeather();
          moveServo();
          setLED();
          //Todo: Timeout and go to sleep
          //      sleeps = 900; // (60/4)*60 = 60 minutes of sleep
    }
    else
    {
          //Don't sleep if the user is pressing the power pin
          if (!digitalRead(ButtonPowerPin)) {
            sleeps--;
            sleep();
          }
    }
}

void CONTROLLER::readLocalWeather() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    localhumidity = _dht->readHumidity();
    localtemp = _dht->readTemperature();
};

void CONTROLLER::requestNetWeather() {
  //Request new forcast
  _serial->print("OK!,");
  _serial->print(localtemp);
  _serial->print(",");
  _serial->print(localhumidity);
  _serial->print("\n");
}

void CONTROLLER::readNetWeather() {
  // Todo: this is a blocking read, we have to wait for the weather, need to break out
  
  // Read weather over /dev/ttyATH0<->Serial1
  String weather = _serial->readStringUntil('\n');
  
  //String weather = "OK!,Cloudy,3,19.00"; //Check,Status,Position,Temperature
  if (!weather.startsWith("OK!")) { return; }  //Todo: Handle case where using local values, Todo: Handle case where the Wifi is in the other mode
  if (!parseWeather(weather)) { return; } // No change in weather
}

bool CONTROLLER::parseWeather(String weather) {
  bool changed = false;
  
  const char separator = ',';
  unsigned int c1 = weather.indexOf(separator);
  unsigned int c2 = weather.indexOf(separator, c1+1);
  unsigned int c3 = weather.indexOf(separator, c2+1);
  // Check if we have 4 values separated with commas
  if (c1 == -1 || c2 == -1 || c3 == -1) { return changed; }

  String sPos = weather.substring(c2+1,c3);
  uint8_t tempPos = sPos.toInt();
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
    _led->SetCurrentRGB(1,1,1);
    _led->SetOffTimesRGB(0x50, 0x52,0x50);
    _led->SetDimmingLevel(0);       // Off
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
  // See https://gist.github.com/wayoda/db3c023417757f726088
    return digitalRead(HandshakePin);
}

void CONTROLLER::moveServo() {
    uint8_t p = position;
    if (p == 0) { p = 3; }           // Default to middle position
    p = constrain(position, 1, 5);   // Ensure position valid
    unsigned int degrees = map(p,1,5,50,100); // Move servo to correct position 50 to 100 degrees
    _servo->write(degrees,10,false); // Slow move, don't wait
}

void CONTROLLER::setLED() {
     //Todo: If colour cycle then get colour from the blinker else get colour from temp
  
     if (nettemp <= 0)                  { _led->SetColor(White);  }
     if (nettemp > 0  && nettemp <= 5)  { _led->SetColor(Purple); }
     if (nettemp > 5  && nettemp <= 10) { _led->SetColor(Blue);   }
     if (nettemp > 10 && nettemp <= 15) { _led->SetColor(Green);  }
     if (nettemp > 15 && nettemp <= 25) { _led->SetColor(Yellow); }
     if (nettemp > 25 && nettemp <= 30) { _led->SetColor(Orange); }
     if (nettemp > 30 )                 { _led->SetColor(Red);    }

     _led->SetDimmingLevel(_blinker->Level());
     
      /* Todo: (should be handled by blinker)
    Off            Off / Sleeping
    Slow Flash	   Booting / Getting data
    Quick Flash    Error (Using Historic or Local Data)
    Colour cycle   Needs configuring
     */
}

void CONTROLLER::sleep() {
  // Sleep the ATMega
  // Need to check servo has finished moving before sleeping, perhaps put that into the run method rather than the sleep call
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

void CONTROLLER::wake() {
    knock = true;
}
