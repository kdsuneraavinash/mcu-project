#include <Arduino.h>

#include "cap/cap.h"
#include "sensor/sensor.h"
#include "utils.h"
#include "wifi/controller.h"

#define CAP_SIZE 1500
#define SAMPLE_BUFFER 30
#define TOTAL_DELAY (60 * 1000)
#define DELAY_TIME (TOTAL_DELAY / (SAMPLE_BUFFER))

float temp_arr[SAMPLE_BUFFER];
float humiditity_arr[SAMPLE_BUFFER];
float pressure_arr[SAMPLE_BUFFER];
float light_arr[SAMPLE_BUFFER];
int sample_index = 0;

sensor toSensorValue(float* buffer) {
  float sensor_mean = mean(buffer, SAMPLE_BUFFER);
  float sensor_std = standard_dev(buffer, SAMPLE_BUFFER, sensor_mean);
  return {sensor_mean, sensor_std};
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  initializeConnection();
}

void loop() {
  if (sample_index == SAMPLE_BUFFER) {
    char cap[CAP_SIZE];
    sensor temp = toSensorValue(temp_arr);
    sensor humidity = toSensorValue(humiditity_arr);
    sensor pressure = toSensorValue(pressure_arr);
    sensor light = toSensorValue(light_arr);
    generateCap(cap, CAP_SIZE, temp, humidity, pressure, light);
    sendSensorData(cap);
    sample_index = 0;
  } else {
    float temp = sampleTemperature();
    float humidity = sampleHumidity();
    float pressure = samplePressure();
    float light = sampleLight();
    temp_arr[sample_index] = temp;
    humiditity_arr[sample_index] = humidity;
    pressure_arr[sample_index] = pressure;
    light_arr[sample_index] = light;
    sample_index++;
  }
  delay(DELAY_TIME);
}
