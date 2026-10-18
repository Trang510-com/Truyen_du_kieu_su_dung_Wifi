#include <WiFi.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";

const char* serverIP = "192.168.4.1";
const int serverPort = 1234;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Ket noi vao AP cua ESP32 so 1
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Dang ket noi AP");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nDa ket noi AP");
  Serial.print("IP ESP32 so 2: ");
  Serial.println(WiFi.localIP());

  while (!client.connect(serverIP, serverPort)) {
    Serial.println("Dang ket noi TCP Server...");
    delay(1000);
  }

  Serial.println("Da ket noi TCP Server");
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      String msg = client.readStringUntil('\n');
      Serial.print("Nhan tu ESP32 so 1: ");
      Serial.println(msg);
    }

    if (Serial.available()) {
      String msg = Serial.readStringUntil('\n');
      client.println(msg);
      Serial.println("Da gui tin nhan");
    }
  } else {
    Serial.println("Mat ket noi TCP Server");
    delay(1000);
  }
}
