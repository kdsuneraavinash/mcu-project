#include <NTPClient.h>
#include <WiFiUdp.h>

#define TIME_ZONE ((11 * 3600) / 2)
#define TIMESTAMP_SIZE 50

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

char formattedDate[50];

/**
 * Initialize NTP connection.
 * The WiFi must ve set-up at this point.
 * */
void initializeNtp() {
  Serial.println("[NTP] Starting NTP connection...");
  timeClient.begin();
  timeClient.setTimeOffset(TIME_ZONE);
  Serial.printf("[NTP] NTP connected in %d time zone.\n", TIME_ZONE);
}

/**
 * Update NTP time and set global variables
 * */
void updateTime() {
  Serial.println("[NTP] Retrieving timestamp via ntp...");
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  String date = timeClient.getFormattedDate();
  date.replace("Z", "+05:30");
  date.toCharArray(formattedDate, TIMESTAMP_SIZE);
  Serial.printf("[NTP] Retrieved timestamp: %s\n", formattedDate);
}
