#include <Arduino.h>
#include <cppQueue.h>

#include "cap/cap.h"
#include "sensor/bmp180.h"
#include "sensor/dht.h"
#include "sensor/sensor.h"
#include "utils.h"
#include "wifi/controller.h"
#include "wifi/ntp.h"

#define CAP_SIZE 3000
#define N_SAMPLES 5
#define CACHE_SIZE 10
#define REMOTE_SERVER "http://7e86ccb1d82f.ngrok.io/"

#define SYNC_PERIOD (30 * 1000)
#define SAMPLE_PERIOD (SYNC_PERIOD / (N_SAMPLES))

float tempSamples[N_SAMPLES];
float humiditySamples[N_SAMPLES];
float pressureSamples[N_SAMPLES];
float lightSamples[N_SAMPLES];
int currentSample = 0;
unsigned long lastSampleMillis;
Queue capQueue(CAP_SIZE, CACHE_SIZE);

void clearSample(float* buffer) {
  for (int i = 0; i < N_SAMPLES; i++) {
    buffer[i] = NULL;
  }
}

void clearSamples() {
  clearSample(tempSamples);
  clearSample(humiditySamples);
  clearSample(pressureSamples);
  clearSample(lightSamples);
}

statistic toStatistic(float* buffer) {
  float sensorMean = mean(buffer, N_SAMPLES);
  float sensorStd = standardDeviation(buffer, N_SAMPLES, sensorMean);
  return {sensorMean, sensorStd};
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  initializeConnection();
  initializeNtp();
  setupIdentifier();
  initializeDHT();
  initializeBMP();
  clearSamples();
}

void loop() {
  if (millis() - lastSampleMillis < SAMPLE_PERIOD) {
    return;
  }

  lastSampleMillis = millis();
  if (currentSample == N_SAMPLES) {
    Serial.println("[MAIN] Starting server sync...");
    char cap[CAP_SIZE];
    statistic temp = toStatistic(tempSamples);
    statistic humidity = toStatistic(humiditySamples);
    statistic pressure = toStatistic(pressureSamples);
    statistic light = toStatistic(lightSamples);
    generateCap(cap, CAP_SIZE, temp, humidity, pressure, light);
    if (capQueue.isFull()) {
      Serial.println("[CACHE] CAP cache full, discarding oldest entry.");
      capQueue.drop();
    }
    capQueue.push(cap);
    char serverAddress[] = REMOTE_SERVER;
    processCapQueue(&capQueue, CAP_SIZE, serverAddress);
    currentSample = 0;
    clearSamples();
  } else {
    Serial.println("[MAIN] Starting sensor sync...");
    float temp = sampleTemperature();
    float humidity = sampleHumidity();
    float pressure = samplePressure();
    float light = sampleLight();
    tempSamples[currentSample] = temp;
    humiditySamples[currentSample] = humidity;
    pressureSamples[currentSample] = pressure;
    lightSamples[currentSample] = light;
    currentSample++;
  }
}
