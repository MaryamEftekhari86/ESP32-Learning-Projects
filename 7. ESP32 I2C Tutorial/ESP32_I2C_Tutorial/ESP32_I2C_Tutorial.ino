#include <Wire.h>
#include <Adafruit_VL53L0X.h>

#define I2C_Freq 100000
#define SDA_PIN  8
#define SCL_PIN  9

// ساخت شیء برای باس I2C اختصاصی روی پین‌های 8 و 9
TwoWire I2C_SensorBus = TwoWire(0);

// ساخت شیء سنسور فاصله سنج
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  delay(2000);

  // راه‌اندازی ارتباط I2C با پین‌های دلخواه
  I2C_SensorBus.begin(SDA_PIN, SCL_PIN, I2C_Freq);
  Serial.println("Initializing VL53L0X sensor...");

  // راه‌اندازی سنسور با استفاده از باس I2C تعریف‌شده (I2C_SensorBus)
  if (!lox.begin(VL53L0X_I2C_ADDR, false, &I2C_SensorBus)) {
    Serial.println(F("Failed to find VL53L0X sensor! Check your wiring."));
    while (1) {
      delay(105);
    }
  }
  
  Serial.println(F("VL53L0X sensor initialized successfully!"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;
  
  // انجام اندازه‌گیری فاصله
  lox.rangingTest(&measure, false); // پارامتر دوم برای دیباگ است

  // بررسی وضعیت دریافت داده معتبر
  if (measure.RangeStatus != 4) {  // عدد 4 یعنی خارج از محدوده یا خطای بازتاب
    Serial.print("Distance: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Target out of range / No obstacle detected");
  }

  delay(500); // مکث نیم ثانیه برای خوانش بعدی
}