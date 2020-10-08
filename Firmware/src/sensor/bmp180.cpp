#include <Adafruit_BMP085.h>
#include <Wire.h>

Adafruit_BMP085 bmp;

void initializeBMP() {
  if (!bmp.begin()) {
    Serial.println("[BMP] Could not find a valid BMP180 sensor.");
  }
}

float readPressure() {
  if (!bmp.begin()) {
    Serial.println("[DHT] Failed to read pressure from BMP sensor.");
    return -1;
  }

  float pressure = bmp.readPressure();
  Serial.printf("[BMP] Pressure read: %f\n", pressure);
  return pressure;
}