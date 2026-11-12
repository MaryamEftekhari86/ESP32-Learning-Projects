#include <WiFi.h>
const char* ssid = "Maryam";
const char* password = "mfm404586";

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to WiFi ..");

  // ۳. صبر کردن تا اتصال برقرار شود
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  // ۴. اتصال موفقیت‌آمیز بود!
  Serial.println("\nConnected to the WiFi network!");
  Serial.print("Local ESP32 IP: ");
  Serial.println(WiFi.localIP()); // آدرس IP برد را چاپ می‌کند
}

void loop() {
  // فعلاً کاری انجام نمی‌شود
}