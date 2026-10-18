#include <WiFi.h>

// Thông tin WiFi do ESP32 tự phát ra (AP Mode)
const char* ap_ssid = "ESP32_AP_Network";
const char* ap_password = "12345678";

// Thông tin WiFi nhà/trường học mà ESP32 sẽ kết nối vào (STA Mode)
const char* sta_ssid = "TP-LINK_D582";
const char* sta_password = "12341234";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Cấu hình ESP32 hoạt động đồng thời cả AP và STATION
  WiFi.mode(WIFI_AP_STA);

  // 1. Thấu lập phát WiFi AP
  Serial.println("[*] Creating ESP32 AP");
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("[+] AP Created with IP Gateway: ");
  Serial.println(WiFi.softAPIP());

  // 2. Bắt đầu kết nối vào mạng WiFi AP bên ngoài (STATION)
  Serial.println("[*] Connecting to WiFi Network");
  WiFi.begin(sta_ssid, sta_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("[+] Connected to the WiFi network with local IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Không cần lặp lại thao tác trong loop()
}
