#include <Arduino.h>

#include "bmp180.h"
#include "dht.h"
#include "ldr.h"

float sampleTemperature() { return readTemperature(); }

float sampleHumidity() { return readHumidity(); }

float samplePressure() { return readPressure(); }

float sampleLight() { return readLightIntensity(); }
