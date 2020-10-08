#include <math.h>

float mean(float* buffer, int size) {
  float sum = 0.0;
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (buffer[i] >= 0) {
      count++;
      sum += buffer[i];
    }
  }
  if (count == -1) return -1;
  return sum / count;
}

float standardDeviation(float* buffer, int size, float mean) {
  float std = 0.0;
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (buffer[i] >= 0) {
      count++;
      std += pow(buffer[i] - mean, 2);
    }
  }
  if (count == -1) return -1;
  return pow(std / count, 0.5);
}
