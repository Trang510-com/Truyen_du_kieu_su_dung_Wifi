
#include <WiFi.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";

WiFiServer server(1234);
WiFiClient client;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password, 6, 0, 4);

  Serial.println("ESP32 dang phat WiFi AP");
  Serial.print("IP AP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  Serial.println("TCP Server da bat dau");
}

void loop() {
  if (!client || !client.connected()) {
    WiFiClient newClient = server.available();
    if (newClient) {
      client = newClient;
      Serial.println("ESP32 so 2 da ket noi");
    }
  }

  if (client && client.connected()) {
    if (client.available()) {
      String msg = client.readStringUntil('\n');
      Serial.print("Nhan tu ESP32 so 2: ");
      Serial.println(msg);
    }

    if (Serial.available()) {
      String msg = Serial.readStringUntil('\n');
      client.println(msg);
      Serial.println("Da gui tin nhan");
    }
  }
}
