#define POT_PIN 1
#define FILTER_LEN 15  

uint32_t potBuffer[FILTER_LEN] = {0};
int bufferIndex = 0;
int rawValue = 0;
int filteredValue = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db); //تضعیف ولتاژ برای اینکه بتوانیم تا 3.3 ولت هم بهش بدیم ولی تبدیل به زیر یک ولت بشه
}

void loop() {
  rawValue = analogRead(POT_PIN);
  filteredValue = calculateMovingAverage(rawValue);
  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print("\t");
  Serial.print("Filtered: ");
  Serial.println(filteredValue);
  delay(10);
}
uint32_t calculateMovingAverage(int newRaw) {
  unsigned long sum = 0;
  potBuffer[bufferIndex] = newRaw;
  bufferIndex++;
  if (bufferIndex >= FILTER_LEN) {
    bufferIndex = 0;
  }
  for (int i = 0; i < FILTER_LEN; i++) {
    sum += potBuffer[i];
  }
  return (sum / FILTER_LEN);
}
