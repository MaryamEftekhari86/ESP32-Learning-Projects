#define GPIO_pin 5

uint32_t Freq = 0;

void setup() 
{
  pinMode(GPIO_pin, OUTPUT); 
  Serial.begin(115200);
  delay(1000);
  Freq = getCpuFrequencyMhz();
  Serial.print("Initial CPU Frequency: ");
  Serial.print(Freq);
  Serial.println(" MHz");


  if(setCpuFrequencyMhz(80)) {
    Serial.println("Successfully changed CPU clock to 80 MHz!");
  } else {
    Serial.println("Failed to change CPU clock frequency!");
  }

  Freq = getCpuFrequencyMhz();
  Serial.print("New CPU Frequency: ");
  Serial.print(Freq);
  Serial.println(" MHz");

  Freq = getXtalFrequencyMhz();
  Serial.print("XTAL Freq = ");
  Serial.print(Freq);
  Serial.println(" MHz");
}

void loop() 
{
  digitalWrite(GPIO_pin, 1);
  digitalWrite(GPIO_pin, 0);
}