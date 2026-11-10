#include <Preferences.h>
Preferences preferences;
#define LED_PIN 8
#define BTN_GPIO 9 

bool ledState = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_GPIO, INPUT_PULLUP); // استفاده از پول‌آپ داخلی برای دکمه

  // باز کردن فضای ذخیره‌سازی با نام "storage"
  preferences.begin("led-app", false);

  // خواندن آخرین وضعیت ذخیره‌شده (اگر مقداری نبود، به صورت پیش‌فرض false در نظر گرفته می‌شود)
  ledState = preferences.getBool("state", false);
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);

  Serial.println("ESP32-C3 SuperMini Initialized. Last LED state loaded!");
}

void loop() {
  // خواندن وضعیت دکمه (چون پول‌آپ است، فشردن دکمه مقدار LOW تولید می‌کند)
  if (digitalRead(BTN_GPIO) == LOW) {
    delay(50); // تأخیر ساده برای جلوگیری از نویز (Debounce)
    if (digitalRead(BTN_GPIO) == LOW) {
      
      // تغییر وضعیت ال‌ای‌دی
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);

      // ذخیره وضعیت جدید در حافظه فلش ماندگار
      preferences.putBool("state", ledState);
      
      Serial.println("LED State Changed & Saved to Flash!");

      // منتظر ماندن تا رها شدن دکمه
      while (digitalRead(BTN_GPIO) == LOW) {
        delay(10);
      }
    }
  }
}