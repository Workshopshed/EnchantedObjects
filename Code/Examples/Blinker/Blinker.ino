#include "Blink.h"

Blinker b(1,0);

void setup() {
  Serial.begin(9600);
  b.Blink(Blink_Cycle);
  pinMode(13, OUTPUT);
}

void loop() {
  Serial.println(b.GetColour());
  digitalWrite(13, b.Level());
}
