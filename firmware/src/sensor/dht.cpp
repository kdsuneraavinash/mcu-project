#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void initializeDHT() { dht.begin(); }

float readHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("[DHT] Failed to read humidity from DHT sensor.");
    return -1;
  }

  Serial.printf("[DHT] Humidity read: %f\n", humidity);
  return humidity;
}

float readTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("[DHT] Failed to read temperature from DHT sensor.");
    return -1;
  }

  Serial.printf("[DHT] Temperature read: %f\n", temperature);
  return temperature;
}
