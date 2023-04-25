#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>

const char* ssid = "Cgates_BF90";
const char* password = "74097494";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from ESP8266!</h1>");
}
