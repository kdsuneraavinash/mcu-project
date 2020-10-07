#include <Arduino.h>

#include "dht.h"

float sampleTemperature() { return readTemperature(); }

float sampleHumidity() { return readHumidity(); }

float samplePressure() { return 300 + (random(10) * 2 - 5); }

float sampleLight() { return 400 + (random(10) * 2 - 5); }
