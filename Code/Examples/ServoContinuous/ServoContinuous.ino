#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 

void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(180);
} 

void loop() 
{ 
  // this space intentionally left blank
} 
