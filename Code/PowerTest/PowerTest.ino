int ledPin = 13;                 // LED connected to pin 13

void setup()
{
  pinMode(ledPin, OUTPUT);      // sets the digital pin as output
  pinMode(A5, OUTPUT);
}

void loop()
{
  digitalWrite(A5, LOW);   // sets the Linino off
  digitalWrite(ledPin, HIGH);   // sets the LED on
  delay(5000);                  // waits for a second
  digitalWrite(A5, HIGH);    // sets the Linino on
  digitalWrite(ledPin, LOW);    // sets the LED off
  delay(5000);                  // waits for a second
}

