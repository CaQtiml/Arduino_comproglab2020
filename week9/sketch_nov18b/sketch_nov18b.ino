#include <M5Stack.h>

#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <SimpleDHT.h>

//#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino

String LINE_TOKEN = "Dsc6p51IBAfueMEavwYkgHXBhb3MW1lDbPhTMLuVtKA";

int temperature, humidity;
SimpleDHT11 dht;

const char* ssid = "HUAWEI nova 2i";  // Wifi Name
const char* password = "12345678";  // Wifi Password

void setup() {
  //  pinMode(ledPin1, OUTPUT); // Set pin as output
  //  pinMode(buttonPin, INPUT); // set pin as input

  WiFi.begin(ssid, password);
  Serial.begin(9600);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //  int reading = digitalRead(buttonPin);
  //  // if the button state has changed:
  //  if (reading != buttonState) {
  //    buttonState = reading;
  //
  //    // only toggle the LED if the new button state is LOW
  //    if (buttonState == LOW) {
  //      ledState = !ledState;
  //      Line_Notify(LINE_TOKEN, "กดปุ่ม ZX-SWITCH01"); // Call funtion
  //      Line_Notify();
  //      delay(100);
  //    }
  //  }
  //  digitalWrite(ledPin1, ledState);  // set the LED:

  if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) {
    float temp, humid;
    int status = dht.read2(5, &temp, &humid, NULL);

    if (status == SimpleDHTErrSuccess) {
      temperature = temp;
      humidity = humid;
    }

    Line_Notify(LINE_TOKEN, StringString(temperature) + " " + String(humidity));
    Serial.println("Sent");
  }

  M5.update();
}

void Line_Notify(String LINE_Token, String message) {
  String msg = String("message=") + message;

  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Authorization: Bearer " + String(LINE_Token) + "\r\n";
  req += "Content-Length: " + String(msg.length()) + "\r\n";
  req += "\r\n";
  req += msg;

  client.print(req);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}
