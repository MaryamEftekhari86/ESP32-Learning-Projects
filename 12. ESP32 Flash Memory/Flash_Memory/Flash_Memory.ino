#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // مدت زمان اسکن به ثانیه
BLEScan* pBLEScan;

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning for BLE devices...");

  // راه‌اندازی ماژول بلوتوث
  BLEDevice::init("");
  
  // تنظیمات اسکنر
  pBLEScan = BLEDevice::getScan(); // ایجاد شیء اسکنر
  pBLEScan->setActiveScan(true);   // اسکن فعال برای گرفتن اطلاعات بیشتر (مثل نام دستگاه‌ها)
  pBLEScan->setInterval(100);      // بازه زمانی اسکن
  pBLEScan->setWindow(99);         // پنجره اسکن
}

void loop() {
  // شروع اسکن (به مدت زمان مشخص شده)
  Serial.println("Starting scan...");
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  
  // نمایش تعداد دستگاه‌های پیدا شده
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  
  // چاپ مشخصات دستگاه‌های پیدا شده در مانیتور سریال
  for (int i = 0; i < foundDevices.getCount(); i++) {
    BLEAdvertisedDevice device = foundDevices.getDevice(i);
    Serial.print("Device Name: ");
    Serial.print(device.getName().c_str());
    Serial.print(" | MAC Address: ");
    Serial.println(device.getAddress().toString().c_str());
  }
  
  Serial.println("Scan done!\n-------------------");
  
  // پاک کردن نتایج از حافظه برای اسکن دوره‌های بعدی
  pBLEScan->clearResults(); 
  
  // 5 ثانیه صبر کردن قبل از اسکن مجدد
  delay(5000);
}