#include "Controller.h"

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial,Blinker *blinker){
  _dht = dht;
  _servo = servo;
  _led = led;
  _serial = serial;
  _blinker = blinker;
  position = 1; // Middle position
  knock = false;
}

void CONTROLLER::begin() {
    delay(2000); // Give things chance to boot
    pinMode(LEDPin, OUTPUT);
    pinMode(LininoPin, OUTPUT);
    pinMode(PowerPin, OUTPUT);
    pinMode(HandshakePin, INPUT);
    pinMode(ButtonPowerPin, INPUT_PULLUP);
    pinMode(ButtonWifiPin, INPUT_PULLUP);
    _blinker->SetColour(White);
    //Servo pin is handled by servo attach
}

void CONTROLLER::run(void) {
          switch (state) {
          case C_Sleeping:
              if (sleeps <= 0 || knock) {
                  state = C_WakeUp;
              } else {
                //Don't sleep if the user is pressing the power pin
                if (!digitalRead(ButtonPowerPin)) {
                  sleeps--;
                  sleep();
                }
              }
              break;
          case C_WakeUp:
              Serial.println("Waking up");
              acknowledge();
              _blinker->Blink(Blink_Long);
              powerOn();
              moveServo(); // Show previous values
              readLocalWeather();
              state = C_Booting;
              break;
          case C_Booting:
              if (isLininoRunning()) {
                Serial.println("Getting Weather");
                requestNetWeather();
                state = C_GettingWeather;
              }
              break;
          case C_GettingWeather:
              if (isReadyNetWeather()) {
                Serial.println("Parsing Weather");
                if (!readNetWeather()) { break;} 
                lininoOff();
                moveServo();
                state = C_Display;
                _DisplayTimeout = millis() + 30000; // Display for 30 seconds
              }
              break;
           case C_Display:
             if (_DisplayTimeout < millis()) {
               Serial.println("Back to sleep");
               _blinker->Blink(Blink_Off);
               powerOff();
               //sleeps = 15; //1 min
               sleeps = 900; // (60/4)*60 = 60 minutes of sleep
               knock = false;               
               state = C_Sleeping;
             }
             break;
        }
        setLED(); 
        
        if (!digitalRead(ButtonWifiPin)) { state = C_Sleeping; }
}

void CONTROLLER::readLocalWeather() {
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    localhumidity = _dht->readHumidity();
    localtemp = _dht->readTemperature();
};

void CONTROLLER::requestNetWeather() {
  delay(1000); //Solid lights for 1 second
}


bool CONTROLLER::isReadyNetWeather() {
   static int count;
   delay(5);
   if (++count > 999) { weatherReady = true; }
   count = count % 1000;
   return weatherReady; 
}

bool CONTROLLER::readNetWeather() {
  //Demo weather, get the weather and cycle through options
  
  String weather = weathers[currentweather]; //Check,Status,Position,Temperature
  currentweather++ % 5;

  Serial.println(weather);
  
  _blinker->Blink(Blink_Solid);

  parseWeather(weather);
  
  return true;
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

  String sTemp = weather.substring(c3+1);
  
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
    digitalWrite(PowerPin, HIGH);    // sets the MOSFET on
    _servo->attach(ServoPin);
    if (_servo->read() == 0) { _servo->write(ServoMid,10,false); };
    _dht->begin();                  
    _led->begin();                //Todo: This calls wire.begin, any issues doing that?
    _led->SetCurrentRGB(1,1,1);
    _led->SetOffTimesRGB(0x50, 0x52,0x50);
    _led->SetDimmingLevel(0);       // Off
}

void CONTROLLER::powerOff() {
    _servo->stop();
    _servo->detach();
    digitalWrite(PowerPin, LOW);    // sets the MOSFET off
}

void CONTROLLER::lininoOn() {
}

void CONTROLLER::lininoOff() {
    lininoRunning = false;
    weatherReady = false;
}

bool CONTROLLER::isLininoRunning() {
   static int count;
   delay(5);
   if (++count > 999) lininoRunning = true;
   count = count % 1000;
   return lininoRunning; 
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

    //Serial.println(nettemp);

     _led->SetDimmingLevel(_blinker->Level());
     _led->SetColor(_blinker->GetColour());
}

void CONTROLLER::sleep() {
     LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

void CONTROLLER::wake() {
    //Called by interupt, keep as short as possible
    knock = true;
}

void CONTROLLER::acknowledge() {
   //let user know something is happening
   digitalWrite(LEDPin, HIGH);
   delay(200);
   digitalWrite(LEDPin, LOW);
   delay(200);
   digitalWrite(LEDPin, HIGH);
   delay(200);
   digitalWrite(LEDPin, LOW);
   delay(200);   
   digitalWrite(LEDPin, HIGH);
   delay(200);
   digitalWrite(LEDPin, LOW);
}


