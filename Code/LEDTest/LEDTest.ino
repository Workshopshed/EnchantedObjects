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
  
  LEDS.SetDimmingLevel(0x0FFF); // Maximum Brightness
  // ...
  // Set RED
  LEDS.SetIntensityRGB(0x0FFF, 0x0000, 0x0000);
  // You can set the colors as well to White, Silver, Gray, Black, Red, Maroon, Yellow, Olive, Lime, Green, Aqua, Teal, Blue, Navy, Fuchsia, Purple
  // ...
  //LEDS.SetColor(Fuchsia);
  // ...
}

void loop() {
  // fade up and down
  
  digitalWrite(13, HIGH);
  
  for (int level = 0x0FFF; level > 1; level--) { 
      LEDS.SetDimmingLevel(level);	// Brightness 
      delay(1); 
  }

  digitalWrite(13, LOW);

  for (int level = 0; level < 0x0FFF; level++) { 
      LEDS.SetDimmingLevel(level);	// Brightness 
      delay(1); 
  }

}
