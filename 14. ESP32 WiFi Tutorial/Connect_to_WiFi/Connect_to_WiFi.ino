#include <WiFi.h>

// نام شبکه وای‌فای و رمز عبور دلخواه خود را اینجا وارد کنید
const char* ssid = "ESP32-C3-Hotspot";
const char* password = "12345678"; // رمز عبور باید حداقل ۸ کاراکتر باشد

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("در حال راه‌اندازی اکسس پوینت...");

  // ساخت شبکه وای‌فای (Access Point)
  WiFi.softAP(ssid, password);

  // دریافت و نمایش آدرس IP برد
  IPAddress IP = WiFi.softAPIP();
  Serial.print("نام شبکه (SSID): ");
  Serial.println(ssid);
  Serial.print("آدرس IP برد: ");
  Serial.println(IP); // معمولاً 192.168.4.1 است
}

void loop() {
  // در این حالت نیازی به قرار دادن کد در حلقه اصلی نیست
}