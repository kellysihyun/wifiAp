#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <IPAddress.h> // 추가

const char* ssid = "";
const char* password = "";
WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.softAP("sihyun", "12345678");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", handleRoot);
  server.on("/connect", handleConnect);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><meta charset='utf-8' name='viewport' content='width=device-width, initial-scale=1.0'></head><body>";
  html += "<h1>접속 가능한 Wifi 정보를 입력해주세요. </h1>";
  html += "<form action='/connect' method='post'>";
  html += "<label for='ssid'>SSID      : </label>";
  html += "<input type='text' id='ssid' name='ssid'><br><br>";
  html += "<label for='password'>Password : </label>";
  html += "<input type='password' id='password' name='password'><br><br>";
  html += "<input type='submit' style='font-size: 20px' value='  전 송  '>";
  html += "</form></body></html>";
  server.send(200, "text/html", html.c_str());
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.println("WiFi 연결 시도 중...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("WiFi 연결 시도중...");
  }
  Serial.println("WiFi에 연결됨");
  Serial.print("WiFi IP 주소: ");
  Serial.println(WiFi.localIP());
  String html = "<html><head><meta charset='utf-8' name='viewport' content='width=device-width, initial-scale=1.0'></head><body>";
  html += "<h1> WiFi 연결 성공 </h1>";
  html += "<h2> >>  ";
  html += ssid;
  html +=" 에 접속을 완료했습니다 </h2>";
  html += "</body></html>";
  server.send(200, "text/html", html.c_str());
}
