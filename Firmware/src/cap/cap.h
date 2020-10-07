#ifndef CAP_H
#define CAP_H

#include "statistic.h"

void generateCap(char* buffer, int buffer_size, statistic temp,
                 statistic humidity, statistic pressure, statistic light);
void setupIdentifier();

#endif