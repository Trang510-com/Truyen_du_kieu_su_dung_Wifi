
#include<WiFi.h>
#include <WiFiAP.h>

const char* ssid = "ESP32";
const char* password = "66668888";

// Dia chi IP tu dat
IPAddress local_IP(192, 168, 10, 1);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);

  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Error!");
    return;
  }

  if (WiFi.softAP(ssid, password)) {
    Serial.println("ESP32 da phat WiFi!");
    Serial.print("Ten WiFi: ");
    Serial.println(ssid);

    Serial.print("IP Gateway: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Khong the khoi dong AP!");
  }
}

void loop() {
}