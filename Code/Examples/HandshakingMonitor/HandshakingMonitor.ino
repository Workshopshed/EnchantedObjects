//Conbination of the YunSerialTerminal example and https://gist.github.com/wayoda/db3c023417757f726088

// We want to light up the Led on Pin 13 when the Linux-machine 
// is up and running. 
int led = 13;

// This is the pin where the handshake signal from the 
// Linux processor is connected
int handshake = 7;

// flag and the status of the handshake 
// signal must be volatile as they are changed by the interupt
volatile int stateChange=0;
volatile int state=0;

long linuxBaud = 250000;

void setup() {
  pinMode(led, OUTPUT);     
  pinMode(handshake,INPUT);
  //read current status of the handshake signal
  state=digitalRead(handshake);
  //switch the Led on/off depending on the current state
  digitalWrite(led, state);   
  //now activate an interrupt routine that monitors the handshake signal	
  attachInterrupt(4,bootStatusChange,CHANGE);
  
  Serial.begin(115200);      // open serial connection via USB-Serial
  Serial1.begin(linuxBaud);  // open serial connection to Linux
}

boolean commandMode = false;

void loop() {
  if (stateChange) {
    //The handshake signal changed
    stateChange=0;
    digitalWrite(led, state);   
  }
  
  // copy from USB-CDC to UART
  int c = Serial.read();              // read from USB-CDC
  if (c != -1) {                      // got anything?
    if (commandMode == false) {       // if we aren't in command mode...
      if (c == '~') {                 //    Tilde '~' key pressed?
        commandMode = true;           //       enter in command mode
      } else {
        Serial1.write(c);             //    otherwise write char to UART
      }
    } else {                          // if we are in command mode...
      if (c == '0') {                 //     '0' key pressed?
        Serial1.begin(57600);         //        set speed to 57600
        Serial.println("Speed set to 57600");
      } else if (c == '1') {          //     '1' key pressed?
        Serial1.begin(115200);        //        set speed to 115200
        Serial.println("Speed set to 115200");
      } else if (c == '2') {          //     '2' key pressed?
        Serial1.begin(250000);        //        set speed to 250000
        Serial.println("Speed set to 250000");
      } else if (c == '3') {          //     '3' key pressed?
        Serial1.begin(500000);        //        set speed to 500000
        Serial.println("Speed set to 500000");
      } else if (c == '~') {          //     '~` key pressed?
                                      //        send "bridge shutdown" command
        Serial1.write((uint8_t *)"\xff\0\0\x05XXXXX\x7f\xf9", 11);
        Serial.println("Sending bridge's shutdown command");
      } else {                        //     any other key pressed?
        Serial1.write('~');           //        write '~' to UART
        Serial1.write(c);             //        write char to UART
      }
      commandMode = false;            //     in all cases exit from command mode
    }
  }

  // copy from UART to USB-CDC
  c = Serial1.read();                 // read from UART
  if (c != -1) {                      // got anything?
    Serial.write(c);                  //    write to USB-CDC
  }
}

void bootStatusChange() {
  // We are called because the handshake signal has changed
  stateChange=1;
  state=digitalRead(handshake);
}




