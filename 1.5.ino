#include <WiFi.h>

String loaiBaoMat(wifi_auth_mode_t kieu) {
  switch (kieu) {
    case WIFI_AUTH_OPEN:            return "Mo (khong mat khau)";
    case WIFI_AUTH_WEP:             return "WEP";
    case WIFI_AUTH_WPA_PSK:         return "WPA";
    case WIFI_AUTH_WPA2_PSK:        return "WPA2";
    case WIFI_AUTH_WPA_WPA2_PSK:    return "WPA/WPA2";
    case WIFI_AUTH_WPA2_ENTERPRISE: return "WPA2 Enterprise";
    case WIFI_AUTH_WPA3_PSK:        return "WPA3";
    case WIFI_AUTH_WPA2_WPA3_PSK:   return "WPA2/WPA3";
    default:                        return "Khac";
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);    
  WiFi.disconnect();      
  delay(100);

  Serial.println("Bat dau quet WiFi...");
}

void loop() {
  int soMang = WiFi.scanNetworks();   

  Serial.println("Quet xong.");
  if (soMang == 0) {
    Serial.println("Khong tim thay mang WiFi nao.");
  } else {
    Serial.print("Tim thay ");
    Serial.print(soMang);
    Serial.println(" mang WiFi:");
    Serial.println("STT | SSID                             | RSSI | Kenh | Bao mat");
    Serial.println("----------------------------------------------------------------");

    for (int i = 0; i < soMang; i++) {
      Serial.print(i + 1);
      Serial.print("   | ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" | ");
      Serial.print(WiFi.RSSI(i));
      Serial.print(" dBm | ");
      Serial.print(WiFi.channel(i));
      Serial.print("  | ");
      Serial.println(loaiBaoMat(WiFi.encryptionType(i)));
    }
  }

  Serial.println();
  WiFi.scanDelete();   
  delay(5000);         
}