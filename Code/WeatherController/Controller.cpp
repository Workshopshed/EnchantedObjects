#include "Controller.h"

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial,Blinker *blinker){
  _dht = dht;
  _servo = servo;
  _led = led;
  _serial = serial;
  _blinker = blinker;
  position = 3; // Middle position
  knock = false;
}

void CONTROLLER::begin() {
    pinMode(LininoPin, OUTPUT);
    pinMode(Powerpin, OUTPUT);
    pinMode(HandshakePin, INPUT);
    pinMode(ButtonPowerPin, INPUT_PULLUP);
    pinMode(ButtonWifiPin, INPUT_PULLUP);
    //Servo pin is handled by 
}

void CONTROLLER::run(void) {
  /*
  todo: Add a state model to make this coding easier
  
  When the board wakes up it checks to see if the sleep counter has reached zero or if knock has been detected and if so It starts up.
  Otherwise it goes back to sleep for another 4 seconds.
  In start up it firstly powers on the peripherals and WiFi module. It then sets the LED colour to be that of the last known temperature.
  Following this it sets the LED to fast flash to indicate it's going to get the weather. It then gets the local temperature and humidity.
  Once the WiFi module has booted it will request the weather.
  On the Linino side the system sends a handshake signal to indicate that it is ready and starts up the Python script to listen to the serial port.
  The Python script makes an API call to the Yahoo weather service, if that errors or times out it will make a "guess" at the weather based on the local conditions provided by the sensor.
  The data is parsed and send back to the ATmega as a simple string.
  Once the weather has been received the system shuts down the WiFi module. It can then update the position and new LED colour which is then solid and starts a timer for 1 minute.
  sleeps = 900; // (60/4)*60 = 60 minutes of sleep
  Once that timer has expired it will shut down the peripherals and go back to sleep.
  */
  
  
    if (sleeps <= 0 || knock)
    {
        knock = false;
        //Todo: Implement asynchronous request / read etc, perhaps a statemodel
          lininoOn();
          powerOn();
          readLocalWeather();
          requestNetWeather();
          readNetWeather();
          moveServo();
          setLED();
    
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
  //Request new forecast
  _serial->print("OK!,");
  _serial->print(localtemp);
  _serial->print(",");
  _serial->print(localhumidity);
  _serial->print("\n");
}


bool CONTROLLER::isReadyNetWeather() {
   return (_serial->available() > 6); 
}

void CONTROLLER::readNetWeather() {
  // This is a blocking read so call isReadyNetWeather() first;
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
    digitalWrite(Powerpin, HIGH);    // sets the MOSFET on
    _servo->attach(ServoPin);
    if (_servo->read() == 0) { _servo->write(ServoMid,10,false); };
    _dht->begin();                  //Todo: Check we can run these more than once
    _led->begin();
    _led->SetCurrentRGB(1,1,1);
    _led->SetOffTimesRGB(0x50, 0x52,0x50);
    _led->SetDimmingLevel(0);       // Off
}

void CONTROLLER::powerOff() {
    _servo->stop();
    _servo->detach();
    digitalWrite(Powerpin, LOW);    // sets the MOSFET off
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
    unsigned int degrees = map(p,1,5,ServoMin,ServoMax); // Move servo to correct position 50 to 100 degrees
    _servo->write(degrees,10,false); // Slow move, don't wait
}

void CONTROLLER::setLED() {
     if (nettemp <= 0)                  { _blinker->SetColour(White);  }
     if (nettemp > 0  && nettemp <= 5)  { _blinker->SetColour(Purple); }
     if (nettemp > 5  && nettemp <= 10) { _blinker->SetColour(Blue);   }
     if (nettemp > 10 && nettemp <= 15) { _blinker->SetColour(Green);  }
     if (nettemp > 15 && nettemp <= 25) { _blinker->SetColour(Yellow); }
     if (nettemp > 25 && nettemp <= 30) { _blinker->SetColour(Orange); }
     if (nettemp > 30 )                 { _blinker->SetColour(Red);    }

     _led->SetDimmingLevel(_blinker->Level());
     _led->SetColor(_blinker->GetColour());
}

void CONTROLLER::sleep() {
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

void CONTROLLER::wake() {
    knock = true;
}
