#include <math.h>

float mean(float* buffer, int size) {
  float sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += buffer[i];
  }
  return sum / size;
}

float standard_dev(float* buffer, int size, float mean) {
  float std = 0.0;
  for (int i = 0; i < size; i++) {
    std += pow(buffer[i] - mean, 2);
  }
  return pow(std / size, 0.5);
}
