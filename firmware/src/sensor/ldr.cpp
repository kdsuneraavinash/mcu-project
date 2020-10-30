#include <Arduino.h>

#define LDRPIN 4

float readLightIntensity() { return analogRead(LDRPIN); }
