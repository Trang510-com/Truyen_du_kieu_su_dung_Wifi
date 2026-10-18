#include <WiFi.h>

// Thông tin AP do ESP32 phát ra
const char* ap_ssid = "ESP32_Limited_AP";
const char* ap_password = "123456789"; // Mật khẩu tối thiểu 8 ký tự

// Cấu hình giới hạn kết nối
const int channel = 1;            // Kênh WiFi (1 - 13)
const int ssid_hidden = 0;        // 0: Hiện SSID, 1: Ẩn SSID
const int max_connection = 2;     // Giới hạn tối đa 2 thiết bị kết nối cùng lúc

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n[*] Creating AP with connection limit...");

  // Bắt đầu phát WiFi AP với tham số giới hạn số lượng thiết bị
  bool result = WiFi.softAP(ap_ssid, ap_password, channel, ssid_hidden, max_connection);

  if (result) {
    Serial.println("[+] AP Created successfully!");
    Serial.print("[+] IP Gateway: ");
    Serial.println(WiFi.softAPIP());
    Serial.print("[+] Max connections allowed: ");
    Serial.println(max_connection);
  } else {
    Serial.println("[-] Failed to create AP!");
  }
}

void loop() {
  // Lấy số lượng thiết bị hiện đang kết nối vào ESP32
  int connected_stations = WiFi.softAPgetStationNum();

  Serial.print("[+] Connected devices: ");
  Serial.print(connected_stations);
  Serial.print(" / ");
  Serial.println(max_connection);

  delay(3000); // Cập nhật trạng thái mỗi 3 giây
}
