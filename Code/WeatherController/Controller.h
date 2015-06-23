#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"
#include "LowPower.h"
#include "Blink.h"

class CONTROLLER {
 private:
  float localtemp;
  float nettemp;
  uint8_t localhumidity;
  int sleeps;
  volatile bool knock; 
  DHT *_dht;
  Stream *_serial;
  VarSpeedServo *_servo;
  InfineonRGB *_led;
  Blinker *_blinker;
  const uint8_t powerpin = 12;
  const uint8_t servoPin = 9;
  const uint8_t LininoPin = A5;
  const uint8_t HandshakePin = 7;
  const uint8_t ButtonWifiPin = A0;
  const uint8_t ButtonPowerPin = A1;
  uint8_t position;
  void powerOn();
  void powerOff();
  void lininoOn();
  void lininoOff();
  bool lininoRunning();
  void readLocalWeather();
  void requestNetWeather();
  void readNetWeather();
  bool parseWeather(String weather);
  void moveServo();
  void setLED();
  void sleep();

 public:
  CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial,Blinker *blinker);
  void begin();
  void run(void);
  void wake();
};
