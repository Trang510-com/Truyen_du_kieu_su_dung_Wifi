#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "14C"; 
const char* password = "12345678";   

WiFiUDP udp;
const int udpPort = 4210;
char packetBuffer[255]; 

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.print("Dang ket noi WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi da ket noi!");
  Serial.print("IP ESP32 Nhan: ");
  Serial.println(WiFi.localIP());

  // Lắng nghe cổng UDP
  udp.begin(udpPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.print("Nhan duoc tin nhan tu ");
    Serial.print(udp.remoteIP());
    Serial.print(": ");
    Serial.println(packetBuffer);
  }
}