#include "Controller.h"
//Todo: Drop process, use serial
#include <Process.h>
#include <avr/power.h>

CONTROLLER::CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led){
  _dht = dht;
  _servo = servo;
  _led = led;
  position = 3; // Middle position
}

void CONTROLLER::begin() {
    power_adc_disable();          //Not using any analogue functionality so can turn it off
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
  // Todo: Swap this technique to use serial rather than process
  Process p;        
  p.begin("python");  
  p.addParameter("/mnt/sda1/Python/GetWeather.py"); 
  p.addParameter("-r " + String(localhumidity));
  p.addParameter("-t " + String(localtemp));
  p.run();      // Run the process and wait for its termination
  String weather = p.readStringUntil('\n');

  // Read weather over /dev/ttyATH0<->Serial1
  
  //String weather = "OK!,Cloudy,3,19.00"; //Check,Status,Position,Temperature
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
    _led->SetCurrentRGB(1,1,1);
    _led->SetOffTimesRGB(0x50, 0x52,0x50);
    _led->SetDimmingLevel(0x0777); // Mid Brightness
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
     if (nettemp <= 0)                  { _led->SetColor(White);  }
     if (nettemp > 0  && nettemp <= 5)  { _led->SetColor(Purple); }
     if (nettemp > 5  && nettemp <= 10) { _led->SetColor(Blue);   }
     if (nettemp > 10 && nettemp <= 15) { _led->SetColor(Green);  }
     if (nettemp > 15 && nettemp <= 25) { _led->SetColor(Yellow); }
     if (nettemp > 25 && nettemp <= 30) { _led->SetColor(Orange); }
     if (nettemp > 30 )                 { _led->SetColor(Red);    }

      /* Todo:
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
  // Todo: Set a flag to indicate that we want to go get the weather
}
