const int externalLedPin = 3;

void setup() {
  pinMode(externalLedPin, OUTPUT);
}

void loop() {
  digitalWrite(externalLedPin, HIGH);
  delay(1000);
  
  digitalWrite(externalLedPin, LOW);
  delay(1000);
}