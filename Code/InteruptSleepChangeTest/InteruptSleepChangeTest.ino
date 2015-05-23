//https://github.com/GreyGnome/EnableInterrupt
//http://www.arduino.cc/en/Reference/Interrupts
//http://gammon.com.au/interrupts
//http://www.arduino.cc/en/reference/volatile
//All the external interupts are taken by communications
//Using "Change" interupts rather than "external" interupts

#include "EnableInterrupt.h"
#include "LowPower.h"

int led = 13;
int myint = 11;
volatile int state = LOW;

void setup()
{
   pinMode(led, OUTPUT);
   pinMode(myint, INPUT);
   enableInterrupt(myint, blink, CHANGE);
   delay(25000); //Time to reprogramme!
}

void loop()
{
   digitalWrite(led, state);
   LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

void blink()
{
   state = !state;
}
