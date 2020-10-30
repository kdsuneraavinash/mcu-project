#ifndef CONFIG_H
#define CONFIG_H

#include <cppQueue.h>

#include "config.h"

void initializeConnection();
bool sendPostRequest(char* message, char* endpoint);
void processCapQueue(Queue* capCache, int capSize, char* endpoint);

#endif