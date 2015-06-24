#include "infineonrgb.h" 
#include "blink.h"
#include <Wire.h> 	// Include this in every new sketch. 
 
InfineonRGB LEDS;	// Create Object 
Blinker blinker(0x0777,0);

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  //Need to turn on our power system
  const uint8_t powerpin = 12;
  pinMode(powerpin, OUTPUT);  
  digitalWrite(powerpin, HIGH);  
  
  delay(200);
  
  LEDS.begin(); // Cycle and set everything to zero. (seems to be blocking...)
  digitalWrite(13, LOW);
  LEDS.SetCurrentRGB(1,1,1);
  LEDS.SetOffTimesRGB(0x50, 0x52,0x50);
  LEDS.SetDimmingLevel(0x0777); // Off
  
  blinker.SetColour(Red);
  blinker.Blink(Blink_Short);
  
  Serial.begin(115200);
  while (!Serial) {
     ; // wait for serial port to connect.
   }  
}

void loop() {
      Serial.println("-----------");
      Serial.print(blinker.Level());
      Serial.print(",");
      Serial.println(blinker.GetColour());
      Serial.println(LEDS.I2CREAD (ADDRESS, READ_DIMMINGLEVEL)); // Read the dimming level
      
      LEDS.SetDimmingLevel(blinker.Level());
      delay(500);
      LEDS.SetColor(blinker.GetColour());
      digitalWrite(13, blinker.Level());
      delay(500);
}
