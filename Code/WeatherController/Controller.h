#include "DHT.h"
#include "infineonrgb.h"
#include "VarSpeedServo.h"
#include "LowPower.h"
#include "Blink.h"

class CONTROLLER {
 private:
  float localtemp;
  float nettemp;
  float localhumidity;
  int sleeps;
  uint8_t state;
typedef enum{
  C_Sleeping,C_WakeUp,C_Booting,C_GettingWeather,C_Display	
  } States;  
  unsigned long _DisplayTimeout;
  volatile bool knock; 
  DHT *_dht;
  Stream *_serial;
  VarSpeedServo *_servo;
  InfineonRGB *_led;
  Blinker *_blinker;
  const uint8_t LEDPin = 13;
  const uint8_t PowerPin = 12;
  const uint8_t ServoPin = 9;
  const uint8_t LininoPin = A5;
  const uint8_t HandshakePin = 7;
  const uint8_t ButtonWifiPin = A0;
  const uint8_t ButtonPowerPin = A1;
  const uint8_t ServoMin = 58;
  const uint8_t ServoMax = 95;
  const uint8_t ServoMid = ServoMin + ((ServoMax-ServoMin)/2);
  uint8_t position;
  void powerOn();
  void powerOff();
  void lininoOn();
  void lininoOff();
  bool isLininoRunning();
  void readLocalWeather();
  void requestNetWeather();
  bool isReadyNetWeather();
  void readNetWeather();
  bool parseWeather(String weather);
  void moveServo();
  void setLED();
  void sleep();
  void acknowledge();
 public:
  CONTROLLER(DHT *dht,VarSpeedServo *servo,InfineonRGB *led,Stream *serial,Blinker *blinker);
  void begin();
  void run(void);
  void wake();
};
