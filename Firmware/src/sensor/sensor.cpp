#include <Arduino.h>

float sampleTemperature() { return 100 + (random(10) * 2 - 5); }

float sampleHumidity() { return 200 + (random(10) * 2 - 5); }

float samplePressure() { return 300 + (random(10) * 2 - 5); }

float sampleLight() { return 400 + (random(10) * 2 - 5); }
