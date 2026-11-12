#include <WiFi.h>

void setup(){
    Serial.begin(115200);
    delay(1000);

    // فعال‌سازی حالت وای‌فای برای مقداردهی اولیه تراشه
    WiFi.mode(WIFI_STA);
    delay(100);

    Serial.print("\nDefault ESP32 MAC Address: ");
    Serial.println(WiFi.macAddress());
}

void loop(){
  // Do Nothing
}