
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// ===== WIFI ROUTER CO INTERNET =====
const char* routerSSID = "14C";
const char* routerPASS = "123456789";

// ===== WIFI LAN NOI BO =====
const char* apSSID = "ESP32_LAN";
const char* apPASS = "12345678";

// ===== THINGSPEAK WRITE API KEY =====
const char* apiKey = "BTTR20JRPLGMXX1J";

// ===== TCP SERVER =====
WiFiServer server(5000);

// Luu du lieu moi nhat
String latestData = "{\"status\":\"Chua co du lieu\"}";

// Thoi gian gui ThingSpeak gan nhat
unsigned long lastUpload = 0;

// ThingSpeak free thuong can cach nhau it nhat 15 giay
const unsigned long uploadInterval = 16000;

// =================================================
// HAM TIM TRUONG SO TRONG JSON
// Vi du: {"device":"ESP32_2","temperature":28.5,"counter":30}
// =================================================
bool getTemperature(String data, float &temperature) {
  int pos = data.indexOf("\"temperature\"");
  if (pos < 0) {
    return false;
  }

  int colon = data.indexOf(':', pos);
  if (colon < 0) {
    return false;
  }

  int endPos = data.indexOf(',', colon);
  if (endPos < 0) {
    endPos = data.indexOf('}', colon);
  }

  if (endPos < 0) {
    return false;
  }

  String value = data.substring(colon + 1, endPos);
  value.trim();

  // Chi chap nhan gia tri so co dinh dang hop le
  if (value.length() == 0) {
    return false;
  }

  char* endPtr;
  float parsed = strtof(value.c_str(), &endPtr);

  if (endPtr == value.c_str() || *endPtr != '\0') {
    return false;
  }

  temperature = parsed;
  return true;
}

// =================================================
// GUI DU LIEU LEN THINGSPEAK
// =================================================
void sendToInternet(String data) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Chua ket noi Internet");
    return;
  }

  float temperature;

  if (!getTemperature(data, temperature)) {
    Serial.println("Khong tim thay truong temperature hop le");
    Serial.println("Du lieu JSON:");
    Serial.println(data);
    return;
  }

  // Gioi han tan suat gui du lieu
  unsigned long now = millis();

  if (lastUpload != 0 &&
      now - lastUpload < uploadInterval) {
    Serial.println("Chua den thoi gian gui ThingSpeak tiep theo");
    return;
  }

  Serial.print("Nhiet do can gui: ");
  Serial.println(temperature, 1);

  WiFiClientSecure secureClient;
  secureClient.setInsecure();

  HTTPClient http;

  String url =
      "https://api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1=" + String(temperature, 1);

  http.setTimeout(10000);

  if (http.begin(secureClient, url)) {
    int code = http.GET();

    Serial.print("HTTP status: ");
    Serial.println(code);

    if (code > 0) {
      String response = http.getString();
      response.trim();

      Serial.print("ThingSpeak Entry ID: ");
      Serial.println(response);

      if (response.toInt() > 0) {
        Serial.println("Da gui du lieu thanh cong!");
        lastUpload = millis();
      } else {
        Serial.println("ThingSpeak chua ghi du lieu.");
        Serial.println("Kiem tra API Key va Channel.");
      }
    } else {
      Serial.print("Loi HTTPS: ");
      Serial.println(http.errorToString(code));
    }

    http.end();
  } else {
    Serial.println("Khong tao duoc ket noi HTTPS");
  }
}

// =================================================
// SETUP
// =================================================
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== ESP32 LAN GATEWAY ===");

  // Bat dong thoi AP va STA
  WiFi.mode(WIFI_AP_STA);

  // Cau hinh mang LAN noi bo
  IPAddress localIP(192, 168, 10, 1);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.softAPConfig(localIP, gateway, subnet);
  bool apOK = WiFi.softAP(apSSID, apPASS);

  if (apOK) {
    Serial.println("Da tao Wi-Fi LAN");
    Serial.print("Ten Wi-Fi: ");
    Serial.println(apSSID);
    Serial.print("IP LAN: ");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println("Tao Wi-Fi LAN that bai");
  }

  // Ket noi router Internet
  Serial.print("Dang ket noi router ");
  Serial.println(routerSSID);

  WiFi.begin(routerSSID, routerPASS);

  unsigned long start = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - start < 20000) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Da ket noi router!");
    Serial.print("IP STA: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Chua ket noi duoc router.");
    Serial.println("Kiem tra SSID va mat khau.");
  }

  // Khoi dong TCP Server
  server.begin();
  Serial.println("TCP Server dang chay cong 5000");
  Serial.println("Cho ESP32 so 2 va so 3 gui du lieu...");
}

// =================================================
// LOOP
// =================================================
void loop() {
  // Chap nhan ket noi TCP tu cac ESP32 client
  WiFiClient client = server.available();

  if (client) {
    client.setTimeout(2000);

    String message = client.readStringUntil('\n');
    message.trim();

    if (message.length() > 0) {
      Serial.print("Nhan tu LAN: ");
      Serial.println(message);

      if (message == "GET") {
        // Gui lai du lieu moi nhat cho client
        client.println(latestData);
        Serial.println("Da tra du lieu cho lenh GET");
      } else {
        // Luu du lieu moi nhat
        latestData = message;

        // Phan hoi TCP
        client.println("OK");

        // Gui du lieu len Internet
        sendToInternet(latestData);
      }
    }

    client.stop();
  }
}
