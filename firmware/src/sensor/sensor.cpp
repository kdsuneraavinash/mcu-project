#include <Arduino.h>

#include "bmp180.h"
#include "dht.h"

float sampleTemperature() { return readTemperature(); }

float sampleHumidity() { return readHumidity(); }

float samplePressure() { return readPressure(); }

float sampleLight() { return 400 + (random(10) * 2 - 5); }
