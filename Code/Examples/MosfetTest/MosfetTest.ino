  const uint8_t powerpin = 12;

void setup() {
  
  //Need to turn on our power system

  pinMode(powerpin, OUTPUT);  

  pinMode(13, OUTPUT);  

}

void loop() {
  delay(1000);
  digitalWrite(powerpin, HIGH);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(powerpin, LOW);
  digitalWrite(13, LOW);
}


