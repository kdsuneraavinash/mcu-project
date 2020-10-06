#include "controller.h"

#include <HTTPClient.h>
#include <WiFi.h>

#define REMOTE_SERVER "http://74d58840cfd1.ngrok.io/"

void initializeConnection() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("Trying to connect to WiFi...");
  delay(1000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected with IP: " + WiFi.localIP().toString());
}

void sendSensorData(char* message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(REMOTE_SERVER);
    int httpResponseCode = http.POST(message);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      const char* errorMessage = http.errorToString(httpResponseCode).c_str();
      Serial.printf("[HTTP] Request failed: %s\n", errorMessage);
    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }
}
