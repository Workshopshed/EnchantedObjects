//Test writing to serial
void setup() {
  Serial.begin(115200);   //To PC
  while (!Serial) {
     ; // wait for serial port to connect.
   }
  
  Serial1.begin(115200);   //To Linino
  float t = 25.4;
  float h = 78;
  Serial1.print("OK!,");
  Serial1.print(t);
  Serial1.print(",");
  Serial1.print(h);
  Serial1.print("\n");
}

void loop() {
  if (Serial1.available() > 0) {
    String weather = Serial1.readStringUntil('\n');
    Serial.println(weather);
  }
}
