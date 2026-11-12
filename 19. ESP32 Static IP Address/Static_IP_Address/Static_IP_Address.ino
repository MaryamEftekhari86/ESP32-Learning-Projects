#include <WiFi.h>
const char* ssid = "Maryam";
const char* password = "mfm404586"; 

IPAddress local_IP(192, 168, 1, 108); // IP ثابتی که می‌خواهید به برد داده شود
IPAddress subnet(255, 255, 255, 0);
IPAddress gateway(192, 168, 1, 1);     // IP مودم شما
IPAddress primaryDNS(192, 168, 1, 1);   // اختیاری

void setup(){
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    
    if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
      Serial.println("Configuration Failed!");
    }
    
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting to WiFi Network ..");
    
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){
}