#define LED_PIN  4
#define POT_PIN  1 
const int freq = 5000;
const int resolution = 12;
const int ledChannel = 1;

void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, freq, resolution);
}
void loop() {
  int potValue = analogRead(POT_PIN);
  Serial.print("ADC Raw Value: ");
  Serial.println(potValue);
  ledcWrite(LED_PIN, potValue);
  delay(10);
}