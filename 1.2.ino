#include <WiFi.h>

const char* ssid     = "UET-Wifi-T3 2.4Ghz"; 

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.print("Đang kết nối tới mạng: ");
  Serial.println(ssid);

  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); 
  }

  Serial.println("\nKết nối WiFi thành công!");
  
  Serial.print("Địa chỉ IP của ESP32 là: ");
  Serial.println(WiFi.localIP());
}

void loop() {
 
}