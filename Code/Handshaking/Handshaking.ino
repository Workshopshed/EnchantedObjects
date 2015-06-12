// We want to light up the Led on Pin 13 when the Linux-machine 
// is up and running. 
int led = 13;

// This is the pin where the handshake signal from the 
// Linux processor is connected
int handshake = 7;

// We install a interrupt on the handshake pin so 
// the interrupt flag and the status of the handshake 
// signal must be volatile
volatile int stateChange=0;
volatile int state=0;


void setup() {                
  pinMode(led, OUTPUT);     
  pinMode(handshake,INPUT);
  //read current status of the handshake signal
  state=digitalRead(handshake);
  //switch the Led on/off depending on the current state
  digitalWrite(led, state);   
  //now activate an interrupt routine that monitors the handshake signal	
  attachInterrupt(4,bootStatusChange,CHANGE);
}

// the loop routine runs over and over again forever:
void loop() {
  if (stateChange) {
    //The handshake signal changed
    stateChange=0;
    digitalWrite(led, state);   
  }
  // Now Do whatever your sketch is supposed to do ...

}

void bootStatusChange() {
  // We are called because the handshake signal has changed
  stateChange=1;
  state=digitalRead(handshake);
}


