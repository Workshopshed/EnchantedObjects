//https://github.com/GreyGnome/EnableInterrupt
//http://www.arduino.cc/en/Reference/Interrupts
//http://gammon.com.au/interrupts
//All the external interupts are taken by communications
//Using "Change" interupts rather than "external" interupts

#include "EnableInterrupt.h"

int myint = 11;

void setup()
{
   Serial.begin(9600);

   pinMode(A0, INPUT_PULLUP);
   pinMode(A1, INPUT_PULLUP);
   enableInterrupt(myint, blink, CHANGE);
   Serial.println("Start");
}

void loop()
{ 
   if (!digitalRead(A0)){ Serial.println("A0");}
   if (!digitalRead(A1)){ Serial.println("A1");}
}

void blink()
{
   Serial.println("Boing");
}
