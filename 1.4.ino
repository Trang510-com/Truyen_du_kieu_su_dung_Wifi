
#include <WiFi.h>

const char* ssid = "tttt";
const char* password = "g3wm66bt";

IPAddress ip(10, 163, 172, 200);
IPAddress dns(10, 163, 172, 188);
IPAddress gateway(10, 163, 172, 188);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);

  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.print("Dang ket noi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Da ket noi Wi-Fi");
  Serial.print("IP cua ESP32: ");
  Serial.println(WiFi.localIP());
}

void loop() {
}
