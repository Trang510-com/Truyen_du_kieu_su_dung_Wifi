#include <WiFi.h>

const char* ssid = "ESP32_LAN";
const char* password = "12345678";

const char* serverIP = "192.168.10.1";
const int serverPort = 5000;

WiFiClient client;

int counter = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Dang ket noi ESP32 so 1");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nDa ket noi mang LAN");
  Serial.print("IP cua ESP32 so 2: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverIP, serverPort)) {
      counter++;

      String data = "{\"device\":\"ESP32_2\","
                    "\"temperature\":28.5,"
                    "\"counter\":" + String(counter) + "}";

      client.println(data);

      String response = client.readStringUntil('\n');

      Serial.print("Da gui: ");
      Serial.println(data);

      Serial.print("Phan hoi: ");
      Serial.println(response);

      client.stop();
    } else {
      Serial.println("Khong ket noi duoc TCP Server");
    }
  } else {
    Serial.println("Mat ket noi Wi-Fi");
  }

  delay(5000);
}