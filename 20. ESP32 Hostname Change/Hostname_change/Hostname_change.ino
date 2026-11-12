#include <WiFi.h>
const char* ssid = "Maryam";
const char* password = "mfm404586";

const char* MyHostName = "ESP32-Test";

void setup(){
    Serial.begin(115200);
    delay(1000);

    WiFi.setHostname(MyHostName);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    Serial.println("\nConnecting to WiFi Network ..");
    
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    Serial.println("\nConnected to the WiFi network!");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
    
    Serial.print("ESP32 HostName: ");
    Serial.println(WiFi.getHostname()); // چاپ نام میزبان فعلی برد
}

void loop(){
}
