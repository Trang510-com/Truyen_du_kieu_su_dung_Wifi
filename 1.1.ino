
#include <WiFi.h>

const char* ssid = "P702";
const char* password ="88888888";

void setup() {
  Serial.begin(115200);

  Serial.println("Dang ket noi Wi-Fi...");

  WiFi.begin(ssid, password);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - startTime < 15000) {
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Ket noi Wi-Fi thanh cong!");
    Serial.print("Dia chi IP cua ESP32: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Ket noi Wi-Fi that bai!");
  }
}

void loop() {
}
