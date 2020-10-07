#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float lastTemperature = 0;
float lastHumidity = 0;

void initializeDHT() { dht.begin(); }

float readHumidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("[DHT] Failed to read humidity from DHT sensor.");
    return lastHumidity;
  }

  Serial.printf("[DHT] Humidity read: %f\n", humidity);
  lastHumidity = humidity;
  return humidity;
}

float readTemperature() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("[DHT] Failed to read temperature from DHT sensor.");
    return lastTemperature;
  }

  Serial.printf("[DHT] Temperature read: %f\n", temperature);
  lastTemperature = temperature;
  return temperature;
}
