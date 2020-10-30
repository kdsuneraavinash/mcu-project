#include "controller.h"

#include <HTTPClient.h>
#include <WiFi.h>
#include <cppQueue.h>

#include "../cap/cap.h"

/**
 * Initializing wifi connection.
 * Configuring wifi module and connecting to the network.
 * */
void initializeConnection() {
  WiFi.begin(SSID, PASSWORD);
  Serial.print("[WIFI] Trying to connect...");
  delay(1000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  const char* ip = WiFi.localIP().toString().c_str();
  Serial.printf("\n[WIFI] Connected to network with IP: %s\n", ip);
}

/**
 * Sending the message body given to the endpoint
 * as a POST request.
 * Will return false if attempt failed.
 * */
bool sendPostRequest(char* message, char* endpoint) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[WIFI] Not connected to a network.");
    return false;
  }

  // Send POST request
  Serial.println("[WIFI] Sending POST request to the server...");
  HTTPClient http;
  http.begin(endpoint);
  int responseCode = http.POST(message);
  String response = http.getString();
  http.end();

  // Connection failed error codes
  if (responseCode < 0) {
    String errorMessage = http.errorToString(responseCode).c_str();
    Serial.printf("[WIFI] Request failed: %s\n", errorMessage.c_str());
    return false;
  }

  // Server returned error code
  if (responseCode != HTTP_CODE_OK) {
    Serial.printf("[WIFI] Server %d Response: %s\n", responseCode,
                  response.c_str());
    return false;
  }

  // Success
  Serial.println("[WIFI] Data sent to the server.");
  return true;
}

void processCapQueue(Queue* capCache, int capSize, char* endpoint) {
  int queueLength = capCache->getCount();
  for (int i = 0; i < queueLength; i++) {
    Serial.printf("[CACHE] retrieved oldest CAP. %d remaining.\n",
                  queueLength - i - 1);
    char cap[capSize];
    capCache->pop(cap);
    bool success = sendPostRequest(cap, endpoint);
    if (!success) {
      Serial.println("[CACHE] Request failed. Readding to cache.");
      capCache->push(cap);
    }
  }
}