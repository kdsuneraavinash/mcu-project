#include <Arduino.h>

#include "wifi/controller.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  initializeConnection();
}

void loop() {
  sendSensorData();
  delay(10000);
}
