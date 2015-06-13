#include "infineonrgb.h" 
#include <Wire.h> 	// Include this in every new sketch. 
 
InfineonRGB LEDS;	// Create Object 

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  LEDS.begin(); // Cycle and set everything to zero.
  digitalWrite(13, LOW);
  LEDS.SetCurrentRGB(1,1,1);
  LEDS.SetOffTimesRGB(0x50, 0x52,0x50);
  LEDS.SetDimmingLevel(0x0777); // Mid Brightness
}

void loop() {
  // fade up and down
  int d = 50;
  LEDS.SetColor(White);
  delay(d);
  LEDS.SetColor(Silver);
  delay(d);
  LEDS.SetColor(Gray);
  delay(d);
  LEDS.SetColor(Black);
  delay(d);  
  LEDS.SetColor(Red);
  delay(d); 
  LEDS.SetColor(Maroon);
  delay(d);
  LEDS.SetColor(Yellow);
  delay(d);
  LEDS.SetColor(Olive);
  delay(d);
  LEDS.SetColor(Lime);
  delay(d);
  LEDS.SetColor(Green);
  delay(d); 
  LEDS.SetColor(Aqua);
  delay(d);
  LEDS.SetColor(Teal);
  delay(d);
  LEDS.SetColor(Blue);
  delay(d); 
  LEDS.SetColor(Navy);
  delay(d);
  LEDS.SetColor(Fuchsia);
  delay(d);
  LEDS.SetColor(Purple);
  delay(d);
}
