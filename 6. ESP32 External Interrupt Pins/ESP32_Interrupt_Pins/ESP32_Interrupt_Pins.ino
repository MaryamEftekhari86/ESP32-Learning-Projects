#define BUTTON_PIN  3
#define LED_PIN     4 
void IRAM_ATTR handleButtonInterrupt() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);
  Serial.println("System Initialized. Press the button!");
}
void loop() {
  delay(1000);
}