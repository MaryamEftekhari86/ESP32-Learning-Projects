#define LED_PIN 4

hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR() {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(LED_PIN, OUTPUT);

    // در نسخه جدید، timerBegin فقط فرکانس را می‌گیرد (مثلاً 1000000 هرتز معادل 1 مگاهرتز یا همان 1 میکروثانیه)
    Timer0_Cfg = timerBegin(1000000);

    // اتصال تابع وقفه (بدون آرگومان سوم اضافی)
    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR);

    // تنظیم آلارم برای اجرای هر 50,000 میکروثانیه (50 میلی‌ثانیه) با تکرار بی‌نهایت (true)
    timerAlarm(Timer0_Cfg, 50000, true, 0);

    Serial.println("Timer Interrupt Initialized!");
}

void loop() {
}