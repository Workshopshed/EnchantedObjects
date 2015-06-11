#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"

class CONTROLLER {
 private:
  float localtemp;
  float nettemp;
  int localhumidity;
  DHT *_dht;
  VarSpeedServo *_servo;
  InfineonRGB *_led;
  int const powerpin = 11;
  byte position;
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
  CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led);
  void begin();
  void run(void);

};
