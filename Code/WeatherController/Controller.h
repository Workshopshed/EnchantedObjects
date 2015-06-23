#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"
#include "LowPower.h"

class CONTROLLER {
 private:
  float localtemp;
  float nettemp;
  uint8_t localhumidity;
  uint8_t sleeps;
  DHT *_dht;
  Stream *_serial;
  VarSpeedServo *_servo;
  InfineonRGB *_led;
  const uint8_t powerpin = 11;
  const uint8_t servoPin = 9;
  const uint8_t LininoPin = A5;
  const uint8_t HandshakePin = 7;
  uint8_t position;
  void powerOn();
  void powerOff();
  void lininoOn();
  void lininoOff();
  bool lininoRunning();
  void readLocalWeather();
  void readNetWeather();
  bool parseWeather(String weather);
  void moveServo();
  void setLED();
  void sleep();

 public:
  CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial);
  void begin();
  void run(void);
  void wake();
};
