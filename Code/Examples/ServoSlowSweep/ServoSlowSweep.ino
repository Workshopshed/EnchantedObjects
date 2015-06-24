#include "VarSpeedServo.h"

/*
Sweep
by BARRAGAN <http://barraganstudio.com>
Adapted by Philip van Allen <philvanallen.com> for the VarSpeedServo.h library (October 2013)
This example code is in the public domain
Sweep a servo back and forth from 50 to 100 degrees, 100-50 degrees
Uses the wait feature of the 2013 version of VarSpeedServo to stop the code until the servo finishes moving
Note that servos usually require more power than is available from the USB port - use an external power supply!
*/
VarSpeedServo myservo; // create servo object to control a servo
// a maximum of eight servo objects can be created
const int servoPin = 9; // the digital pin used for the servo
void setup() {
  //Need to turn on our power system
  const uint8_t powerpin = 12;
  pinMode(powerpin, OUTPUT);  
  digitalWrite(powerpin, HIGH);
  
  myservo.attach(servoPin); // attaches the servo on pin 9 to the servo object
  myservo.write(75,10,true); // set the intial position of the servo, slow, wait until done.
}
void loop() {
  myservo.write(50,10,true); // move the servo to 180, max speed, wait until done
  // write(degrees 0-180, speed 1-255, wait to complete true-false)
  delay(500);
  myservo.write(100,10,true); // move the servo to 180, slow speed, wait until done
  delay(500);
}

