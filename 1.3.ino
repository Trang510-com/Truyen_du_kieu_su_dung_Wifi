#include <WiFi.h>

// Thay đổi thông tin WiFi của bạn tại đây
const char* ssid = "TP-LINK_D582";
const char* password = "12341234";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Kết nối tới mạng WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connected to the WiFi network");
  
  // In các thông tin về Access Point và mạng theo yêu cầu đề bài
  Serial.print("[*] Network information for ");
  Serial.println(ssid);
  
  // 1. Địa chỉ MAC / BSSID của Access Point
  Serial.print("[+] BSSID : ");
  Serial.println(WiFi.BSSIDstr());
  
  // 2. Địa chỉ IP của Gateway (Cổng mạng)
  Serial.print("[+] Gateway IP : ");
  Serial.println(WiFi.gatewayIP());
  
  // 3. Subnet Mask
  Serial.print("[+] Subnet Mask : ");
  Serial.println(WiFi.subnetMask());
  
  // 4. Cường độ tín hiệu WiFi (RSSI)
  Serial.print("[+] RSSI : ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dB");
  
  // 5. Địa chỉ IP của ESP32 (cấp bởi DHCP)
  Serial.print("[+] ESP32 IP : ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Không cần thực hiện thao tác lặp lại trong bài này
}
