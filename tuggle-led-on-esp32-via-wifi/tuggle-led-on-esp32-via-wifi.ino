/* The following code based on https://qiita.com/northVil/items/fbdb2c3a52ebc32eaf7f */

#include <WiFi.h>
#include <WebServer.h>

const char *SSID = "IODATA-xxxxxx-2G";
const char *PASS = "XXXXXXXXXXXXX";
const int LED_PIN = 5;

WebServer Server(80);

void SendMessage() {
  Serial.println("Sent message.");
  String message = "<html lang='ja'><input type='checkbox' onclick='location.href=\"/on\"' style='width: 200px; height: 200px'></html>";
  Server.send(200, "text/html", message);
}

void SendOnMessage() {
  Serial.println("Sent ON message.");
  String message = "<html lang='ja'><input type='checkbox' checked='true' onclick='location.href=\"\off\"' style='width: 200px; height: 200px'></html>";
  Server.send(200, "text/html", message);
  digitalWrite(LED_PIN, HIGH);
}

void SendOffMessage() {
  Serial.println("Sent OFF message.");
  String message = "<html lang='ja'><input type='checkbox' onclick='location.href=\"\on\"' style='width: 200px; height: 200px'></html>";
  Server.send(200, "text/html", message);
  digitalWrite(LED_PIN, LOW);
}

void SendNotFound() {
  Serial.println("Sent NotFound.");
  Server.send(404, "text/plain", "404 not found...");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting...");

  pinMode(LED_PIN, OUTPUT);

  delay(100);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASS);

  Serial.println("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    if (WiFi.status() == WL_CONNECT_FAILED) {
      Serial.println("Can't connect.");
    }
  }

  Serial.println("Connected.");

  Serial.println(WiFi.localIP());

  Server.on("/", SendMessage);
  Server.on("/on", SendOnMessage);
  Server.on("/off", SendOffMessage);
  Server.onNotFound(SendNotFound);

  Server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Server.handleClient();
}
