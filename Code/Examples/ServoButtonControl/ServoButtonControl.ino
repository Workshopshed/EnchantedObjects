#include "VarSpeedServo.h"

const int servoPin = 9; // the digital pin used for the servo
int angle = 75;


void setup() {
  //Need to turn on our power system
  const uint8_t powerpin = 12;
  pinMode(powerpin, OUTPUT);  
  digitalWrite(powerpin, HIGH);
   pinMode(A0, INPUT_PULLUP);
   pinMode(A1, INPUT_PULLUP);  
  
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
  myservo.write(angle,10,true); // set the intial position of the servo, slow, wait until done.
}
void loop() {
  if (!digitalRead(A0)){ 
    Serial.println(++angle);
  }
  if (!digitalRead(A1)){ 
    Serial.println(--angle);
  }
  myservo.write(angle,10,true); // move wait until done.
}

