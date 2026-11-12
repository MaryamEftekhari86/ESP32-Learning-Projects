#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("System Ready. Starting WiFi Scan...");
}

void loop() {
  Serial.println("\nScanning nearby networks...");

  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    Serial.println("No networks found!");
  } else {
    Serial.print(n);
    Serial.println(" networks found:");
    Serial.println("Nr | SSID                 | RSSI | CH | Encryption");
    
    for (int i = 0; i < n; ++i) {
      Serial.printf("%2d", i + 1);
      Serial.print(" | ");
      Serial.printf("%-20.20s", WiFi.SSID(i).c_str());
      Serial.print(" | ");
      Serial.printf("%4d", WiFi.RSSI(i));
      Serial.print(" dBm | ");
      Serial.printf("%2d", WiFi.channel(i));
      Serial.print(" | ");
      
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:
          Serial.print("OPEN");
          break;
        case WIFI_AUTH_WPA_PSK:
          Serial.print("WPA");
          break;
        case WIFI_AUTH_WPA2_PSK:
          Serial.print("WPA2");
          break;
        case WIFI_AUTH_WPA3_PSK:
          Serial.print("WPA3");
          break;
        default:
          Serial.print("Other");
      }
      Serial.println();
      delay(10);
    }
  }

  WiFi.scanDelete();
  delay(5000);
}
