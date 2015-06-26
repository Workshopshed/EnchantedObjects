#include "Blink.h"

Blinker b(1,0);

void setup() {
  Serial.begin(9600);
  b.Blink(Short_Blink);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, b.Level());
  
}
