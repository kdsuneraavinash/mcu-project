#include <Arduino.h>

#include "cap/cap.h"
#include "wifi/controller.h"

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  initializeConnection();
}

void loop() {
  char sensordata[1500];
  sensor temp = {1.0, 10.0};
  sensor humidity = {12.0, 120.0};
  sensor pressure = {13.0, 130.0};
  sensor light = {14.0, 140.0};
  generateCap(sensordata, 1500, temp, humidity, pressure, light);
  sendSensorData(sensordata);
  delay(10000);
}
