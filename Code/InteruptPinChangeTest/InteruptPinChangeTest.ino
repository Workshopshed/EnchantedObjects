//https://github.com/GreyGnome/EnableInterrupt
//http://www.arduino.cc/en/Reference/Interrupts
//http://gammon.com.au/interrupts
//All the external interupts are taken by communications
//Using "Change" interupts rather than "external" interupts

#include "EnableInterrupt.h"

int led = 13;
int myint = 11;
volatile int state = LOW;

void setup()
{
   pinMode(led, OUTPUT);
   enableInterrupt(myint, blink, CHANGE);
}

void loop()
{
   digitalWrite(led, state);
}

void blink()
{
   state = !state;
}
