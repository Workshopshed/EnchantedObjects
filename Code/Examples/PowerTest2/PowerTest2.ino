//Library from http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/#sthash.PhJ0PF9f.dpuf
#include "LowPower.h"

int ledPin = 13;                 // LED connected to pin 13

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(A5, OUTPUT);
  delay(25000);                 // put in a start up delay to make it easier to re-programme
}

void loop()
{
  digitalWrite(A5, HIGH);    // sets the Linino on
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(8000);

  digitalWrite(A5, LOW);   // sets the Linino off
  digitalWrite(ledPin, HIGH);   // sets the LED on

  delay(8000);                  // waits for a second
  digitalWrite(ledPin, LOW);   // both lights off, power and P13
  
  //Sleep
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

