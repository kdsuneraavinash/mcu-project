#ifndef NTP_H
#define NTP_H

#include <WString.h>

extern String formattedDate;
extern String dayStamp;
extern String timeStamp;

void initializeNtp();
void updateTime();

#endif