//Test writing to serial
void setup() {
  Serial.begin(115200);   //To PC
  float t = 25.4;
  float h = 78;
  Serial.print("OK!,");
  Serial.print(t);
  Serial.print(",");
  Serial.print(h);
  Serial.print("\n");
}

void loop() {
}
