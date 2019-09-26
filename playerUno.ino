/*Description: Play RPS using two USB connected 
 * esp8266 device. When pressed flash, it triggers
 * a call to a github.io html page for displaying result.
 * 
 * Have fun playing ;)
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const char* ssid     = "wifiname";
const char* password = "*wifipass";

// get this from the wia dashboard. it should start with `d_sk`

const char* device_secret_key = "uwu a secret";

boolean buttonState = HIGH;
boolean buttonDown = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(0);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is LOW:
  if (buttonState == LOW) {
    if (buttonDown == false) {
      Serial.println("Button Pushed");
      buttonDown = true;
      postToWia();
      delay(750);
    }
  } else {
    buttonDown = false;
  }
}

void postToWia() {
  // wait for WiFi connection
  if((WiFiMulti.run() == WL_CONNECTED)) {
    HTTPClient http;
    USE_SERIAL.print("[HTTP] begin...\n");
    // configure wia rest api
    http.begin("http://api.wia.io/v1/events");
    USE_SERIAL.print("[HTTP] POST...\n");

    // set authorization token
    http.addHeader("Authorization", "Bearer " + String(device_secret_key));
    // set content-type to json
    http.addHeader("Content-Type", "application/json");
    // start connection and send HTTP headers. replace name and data values with your own.
    int httpCode = http.POST("{\"name\":\"buttonPress\"}");
    // httpCode will be negative on error

    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);
        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.println(payload);
        }
    } else {
        USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  }
}
