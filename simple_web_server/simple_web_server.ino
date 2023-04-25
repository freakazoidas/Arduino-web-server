#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TimeLib.h>
#include <WiFiUdp.h>

const char* ssid = "Cgates_BF90";
const char* password = "74097494";

const int ledPin = LED_BUILTIN;

WiFiUDP ntpUDP;
IPAddress timeServerIP;
const char* ntpServerName = "pool.ntp.org";
const int timeZone = 2;  // Central European Time
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];

ESP8266WebServer server(80);

void handleRoot();
void handleToggle();
void handleTime();
time_t getNtpTime();
void sendNTPpacket(IPAddress& address);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ntpUDP.begin(2390);

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/time", handleTime);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  static uint32_t lastUpdateTime = 0;
  if (millis() - lastUpdateTime > 10000) { // Update every 10 seconds
    setTime(getNtpTime());
    lastUpdateTime = millis();
  }
}

void handleRoot() {
  String html = R"(<html>
<head>
  <title>Simple Web Server</title>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
  <script>
    function fetchTime() {
      var xhr = new XMLHttpRequest();
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
          document.getElementById("time").innerHTML = xhr.responseText;
        }
      };
      xhr.open("GET", "/time", true);
      xhr.send();
    }

    setInterval(fetchTime, 1000);
  </script>
</head>
<body>
  <div class="container">
    <div class="row">
      <div class="col">
        <h1>Current time: <span id="time">Loading...</span></h1>
      </div>
    </div>
    <div class="row">
      <div class="col">
        <button class="btn btn-primary" onclick="location.href='/toggle'">Toggle LED</button>
      </div>
    </div>
  </div>
</body>
</html>)";

  server.send(200, "text/html", html);
}

void handleToggle() {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleTime() {
  String currentTime = timeStatus() == timeNotSet ? "Not Set" : String(hour()) + ":" + String(minute()) + ":" + String(second());
  server.send(200, "text/plain", currentTime);
}

time_t getNtpTime() {
  while (ntpUDP.parsePacket() > 0);  // discard any previously received packets
  
  WiFi.hostByName(ntpServerName, timeServerIP);
  sendNTPpacket(timeServerIP);

  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = ntpUDP.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      ntpUDP.read(packetBuffer, NTP_PACKET_SIZE);
      unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
      unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
      unsigned long secsSince1900 = highWord << 16 | lowWord;
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }

  return 0; // return 0 if unable to get the NTP time
}

void sendNTPpacket(IPAddress& address) {
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;  // LI, Version, Mode
  packetBuffer[1] = 0;           // Stratum, or type of clock
  packetBuffer[2] = 6;           // Polling Interval
  packetBuffer[3] = 0xEC;        // Peer Clock Precision

  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  ntpUDP.beginPacket(address, 123);  // NTP requests are to port 123
  ntpUDP.write(packetBuffer, NTP_PACKET_SIZE);
  ntpUDP.endPacket();
}
