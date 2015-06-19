void setup() {
  Serial.begin(115200);   //To PC
  Serial1.begin(115200);  //To Linino
  Serial.print ("Echo...");
}

void loop() {
   //From PC to Linino
  int c = Serial.read();              // read from USB-CDC
  if (c != -1) {                 
     Serial1.write(c);             //        write char to UART
  }
  
  //From Linino to PC
  c = Serial1.read();                 // read from UART
  if (c != -1) {                      // got anything?
    Serial.write(c);                  //    write to USB-CDC
  }
}
