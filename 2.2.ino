#include <WiFi.h>
#include <esp_wifi.h>

const char* ap_ssid = "Thu";
const char* ap_pass = "83868386";   

String macToString(const uint8_t* mac) {
  char buf[18];
  snprintf(buf, sizeof(buf), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buf);
}

void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
  switch (event) {
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
      Serial.print("[+] Thiet bi ket noi, MAC: ");
      Serial.println(macToString(info.wifi_ap_staconnected.mac));
      break;

    case ARDUINO_EVENT_WIFI_AP_STAIPASSIGNED:
      Serial.print("[i] IP duoc cap cho thiet bi: ");
      Serial.println(IPAddress(info.wifi_ap_staipassigned.ip.addr));
      break;

    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
      Serial.print("[-] Thiet bi ngat ket noi, MAC: ");
      Serial.println(macToString(info.wifi_ap_stadisconnected.mac));
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.onEvent(onWiFiEvent);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_pass);

  Serial.println();
  Serial.println("ESP32 da phat WiFi (AP).");
  Serial.print("SSID: ");
  Serial.println(ap_ssid);
  Serial.print("IP / Gateway cua AP: ");
  Serial.println(WiFi.softAPIP());   
  Serial.print("MAC cua AP: ");
  Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  wifi_sta_list_t staList;
  esp_wifi_ap_get_sta_list(&staList);

  Serial.print("So thiet bi dang ket noi: ");
  Serial.println(staList.num);

  for (int i = 0; i < staList.num; i++) {
    Serial.print("  ");
    Serial.print(i + 1);
    Serial.print(". MAC: ");
    Serial.println(macToString(staList.sta[i].mac));
  }
  Serial.println("-----------------------------");
  delay(5000);
}