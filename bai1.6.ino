#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "TP-LINK_D582"; // Tên WiFi chung
const char* password = "12341234";     // Mật khẩu WiFi

WiFiUDP udp;
const char* targetIP = "192.168.1.50"; // Thay IP này bằng IP của ESP32 Nhận (Receiver)
const int udpPort = 4210;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Dang ket noi WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi da ket noi!");
  Serial.print("IP ESP32 Gui: ");
  Serial.println(WiFi.localIP());

  udp.begin(udpPort);
}

void loop() {
  // Gửi tin nhắn mỗi 3 giây
  Serial.println("Dang gui tin nhan...");
  udp.beginPacket(targetIP, udpPort);
  udp.print("Xin chao tu ESP32 Gui!");
  udp.endPacket();

  delay(3000);
}
