#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include "esp_wps.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


// Replace with your network credentials
const char* ssid = "xxxxxxx";
const char* password = "yyyyyyy";

// Variable to store the HTTP request
String header;
String header2;

// Assign output variables to GPIO pins
const int relay1 = 2;
const int relay2 = 15;
const int relay3 = 5;
const int relay4 = 4;
//relays status
int relay1_status = 0;
int relay2_status = 0;
int relay3_status = 0;
int relay4_status = 0;
//Other test variable
const char *htmlindex= "/index.html";
// Function read relays status
void relays_status(){
  relay1_status = digitalRead(relay1);
  relay2_status = digitalRead(relay2);
  relay3_status = digitalRead(relay3);
  relay4_status = digitalRead(relay4);
}

void setup() {

// Initialize the output variables as outputs
pinMode(relay1, OUTPUT);
pinMode(relay2, OUTPUT);
pinMode(relay3, OUTPUT);
pinMode(relay4, OUTPUT);

//start Serial
Serial.begin(115200);
while (!Serial);

//Error detection
if (!SPIFFS.begin(true)) {
  Serial.println("An Error has occurred while mounting SPIFFS");
  return;
}
// Connect to Wi-Fi network with SSID and password
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
}
// Print local IP address and start web server
Serial.println("");
Serial.println("WiFi connectedddd.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

//-----------Route for root / web page-----------
server.on("/", HTTP_ANY, [](AsyncWebServerRequest * request) {
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay1_on web page-----------
server.on("/relay1_on", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay1,HIGH);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay1 web page-----------
server.on("/relay1_off", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay1,LOW);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay2_on web page-----------
server.on("/relay2_on", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay2,HIGH);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay2 web page-----------
server.on("/relay2_off", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay2,LOW);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay3_on web page-----------
server.on("/relay3_on", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay3,HIGH);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay3 web page-----------
server.on("/relay3_off", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay3,LOW);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay4_on web page-----------
server.on("/relay4_on", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay4,HIGH);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relay4 web page-----------
server.on("/relay4_off", HTTP_ANY, [](AsyncWebServerRequest * request) {
  digitalWrite(relay4,LOW);
  request->send(SPIFFS, "/index.html", String());
});

//-----------Route for /relays web page-----------
server.on("/relays", HTTP_ANY, [](AsyncWebServerRequest * request) {
      relays_status();
      String relays_str = "relay1=" + String(relay1_status, DEC) +
                          "; relay2=" + String(relay2_status, DEC) +
                          "; relay3=" + String(relay3_status, DEC) +
                          "; relay4=" + String(relay4_status, DEC);                  
    request->send(200, "text/html", relays_str);
});



//-----------Start server-----------
server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
}
