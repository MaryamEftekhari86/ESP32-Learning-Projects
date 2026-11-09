#define POT_PIN 1

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);
}

void loop() {
  int rawValue = analogRead(POT_PIN);
  uint32_t voltageMilliVolts = analogReadMilliVolts(POT_PIN);
  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | Calibrated Voltage: ");
  Serial.print(voltageMilliVolts / 1000.0);
  Serial.println(" V");
  delay(200);
}
