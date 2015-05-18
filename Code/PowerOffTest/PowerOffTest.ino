/*
  Running shell commands using Process class.
  based on http://arduino.cc/en/Tutorial/ShellCommands
 */

#include <Process.h>

int ledPin = 13;                 // LED connected to pin 13

void setup() {
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output  
  
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);    // sets the Linino on
  
  Bridge.begin();	// Initialize the Bridge
  
  delay(5000);
  
  Process p;
  p.runShellCommandAsynchronously("poweroff"); // Run in background so process returns

  digitalWrite(ledPin, HIGH);   // sets the LED on
}

void loop() {
}



