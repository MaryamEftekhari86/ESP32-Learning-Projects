#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// پین LED داخلی روی برد ESP32-C3 SuperMini
#define LED_PIN 8

// تعریف UUID های استاندارد UART برای BLE
#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

bool deviceConnected = false;
BLECharacteristic *pTxCharacteristic;
unsigned long lastSendTime = 0;
int counter = 0;

// کلاس مدیریت وضعیت اتصال
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Phone Connected!");
    }
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Phone Disconnected!");
      // شروع مجدد تبلیغ برای اتصال مجدد
      pServer->getAdvertising()->start(); 
    }
};

// کلاس مدیریت داده‌های دریافتی از گوشی (RX)
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String rxValue = pCharacteristic->getValue();

      if (rxValue.length() > 0) {
        Serial.print("Received from phone: ");
        Serial.println(rxValue);

        rxValue.trim(); // حذف فاصله‌های اضافه یا کاراکترهای کنترلی

        // برعکس کردن منطق برای تطبیق با سخت‌افزار برد
        if (rxValue == "led_on") {
          digitalWrite(LED_PIN, LOW); // با LOW چراغ روشن می‌شود
          Serial.println("-> LED turned ON");
        } 
        else if (rxValue == "led_off") {
          digitalWrite(LED_PIN, HIGH); // با HIGH چراغ خاموش می‌شود
          Serial.println("-> LED turned OFF");
        }
      }
    }
};
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // راه‌اندازی ماژول BLE با نام دلخواه
  BLEDevice::init("C3-SuperMini-BT");

  // ایجاد سرور BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // ایجاد سرویس BLE
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // ایجاد ویژگی TX (برای ارسال داده از برد به گوشی)
  pTxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_TX,
                        BLECharacteristic::PROPERTY_NOTIFY
                      );
  pTxCharacteristic->addDescriptor(new BLE2902());

  // ایجاد ویژگی RX (برای دریافت داده از گوشی به برد)
  BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID_RX,
                        BLECharacteristic::PROPERTY_WRITE
                      );
  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // شروع سرویس
  pService->start();

  // تنظیمات و شروع Advertising (بخش اصلاح‌شده)
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // کمک به اتصال پایدارتر با آیفون/اندروید
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("Waiting for a smartphone connection...");
}

void loop() {
  // اگر گوشی متصل بود، هر 1 ثانیه یک پیام تستی به همراه شمارنده به گوشی بفرست
  if (deviceConnected) {
    if (millis() - lastSendTime > 1000) {
      lastSendTime = millis();
      counter++;
      
      String txData = "Hello from ESP32-C3! Count: " + String(counter);
      
      pTxCharacteristic->setValue(txData.c_str());
      pTxCharacteristic->notify();
      
      Serial.print("Sent to phone: ");
      Serial.println(txData);
    }
  }
  delay(20);
}