#include <WiFi.h>

const char* ssid = "Maryam";
const char* password = "mfm404586";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\nConnected to the WiFi network!");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // دریافت مقدار قدرت سیگنال (RSSI)
  int rssi = WiFi.RSSI();
  
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.print(" dBm | Signal Quality: ");

  if (rssi > -30) {
    Serial.println("Amazing");
  } else if (rssi >= -55) {
    Serial.println("Very good signal");
  } else if (rssi >= -67) {
    Serial.println("Fairly Good");
  } else if (rssi >= -70) {
    Serial.println("Okay");
  } else if (rssi >= -80) {
    Serial.println("Not good");
  } else if (rssi >= -90) {
    Serial.println("Extremely weak signal");
  } else {
    Serial.println("Unusable / Disconnected");
  }

  delay(5000);
}