#include <Arduino.h>

// تعیین آدرس پارتیشن اختصاصی NVM
const uint32_t NVM_Offset = 0x290000;
uint8_t FLASH_Address = 0;
#define LED_GPIO 4 
#define BTN_GPIO 5
int ledState = LOW;
int btnState = HIGH;
int lastBtnState = HIGH;
unsigned long lastDebounceTime = 0; //تاخیر میدیم که نویز های ابتدای فشردن دکمه از بین بره 
unsigned long debounceDelay = 50;
template<typename T> //اینو نوشتیم که برای هر دیتاتایپ جدیدی نیاز به تعریف تابع جداگونه نباشه
void FlashWrite(uint32_t address, const T& value) {
  //داده ها روی فلش یابت به یابت خوانده میشن ولی نوشتن یا پاک کردن با واحدهای بزگتری به نام سکتور انجام میشه ما قبل از نوشتن سکتور های قبلی رو پاک میکنیم
  ESP.flashEraseSector((NVM_Offset + address) / 4096);
  ESP.flashWrite(NVM_Offset + address, (uint32_t*)&value, sizeof(value));
}
template<typename T>
void FlashRead(uint32_t address, T& value) {
  ESP.flashRead(NVM_Offset + address, (uint32_t*)&value, sizeof(value));
}

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_GPIO, OUTPUT);
  pinMode(BTN_GPIO, INPUT_PULLUP); // استفاده از پول‌آپ داخلی برای دکمه

  // خواندن آخرین وضعیت ذخیره‌شده از فلش هنگام شروع به کار تراشه
  FlashRead<int>(FLASH_Address, ledState);
  
  // اگر مقدار اولیه نامعتبر بود، آن را پیش‌فرض LOW کن
  if (ledState != HIGH && ledState != LOW) {
    ledState = LOW;
  }

  digitalWrite(LED_GPIO, ledState);
  Serial.print("Initial LED State Loaded From Flash: ");
  Serial.println(ledState);
}

void loop() {
  int reading = digitalRead(BTN_GPIO);

  // اگر وضعیت پین دکمه تغییر کرد، زمان را برای فیلتر کردن نویز ریست کن
  if (reading != lastBtnState) {
    lastDebounceTime = millis();
  }

  // بررسی گذشتن زمان تاخیر برای پایداری وضعیت دکمه
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != btnState) {
      btnState = reading;

      // چون از INPUT_PULLUP استفاده کردیم، فشردن دکمه سطح LOW تولید می‌کند
      if (btnState == LOW) {
        ledState = !ledState;               // معکوس کردن وضعیت LED
        digitalWrite(LED_GPIO, ledState);    // اعمال وضعیت جدید روی پایه LED
        
        // ذخیره کردن وضعیت جدید در حافظه فلش
        FlashWrite<int>(FLASH_Address, ledState);
        Serial.println("LED State Changed & Saved Permanently To FLASH!");
      }
    }
  }

  lastBtnState = reading;
}