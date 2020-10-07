#include <Arduino.h>
#include <esp_system.h>
#include <stdio.h>

#include "../wifi/ntp.h"
#include "statistic.h"

#define IDENTIFIER_LENGTH 8

const char* CAP_TEMPLATE =
    "<?xml version = \"1.0\" encoding = \"UTF-8\"?>"
    "<alert xmlns = \"urn:oasis:names:tc:emergency:cap:1.2\">"
    "   <identifier>%s-%d</identifier>"
    "   <sender>MCU_DEVICE</sender>"
    "   <sent>%s</sent>"
    "   <status>Actual</status>"
    "   <msgType>Alert</msgType>"
    "   <scope>Private</scope>"
    "   <info>"
    "       <category>Env</category>"
    "       <event>SENSOR_DATA</event>"
    "       <responseType>None</responseType> "
    "       <urgency>Unknown</urgency>"
    "       <severity>Minor</severity>"
    "       <certainty>Observed</certainty>"
    "       <senderName>mcu_session_%s</senderName>"
    "       <parameter>"
    "           <valueName>TEMP_MEAN</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>TEMP_STD</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>HUMIDITY_MEAN</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>HUMIDITY_STD</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>PRESSURE_MEAN</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>PRESSURE_STD</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>LIGHT_MEAN</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "       <parameter>"
    "           <valueName>LIGHT_STD</valueName>"
    "           <value>%f</value>"
    "       </parameter>"
    "   </info>"
    "</alert>";

int currentIdentifier = 0;
char randomIdentifier[IDENTIFIER_LENGTH + 1];

void setupIdentifier() {
  for (int i = 0; i < IDENTIFIER_LENGTH; i++) {
    byte randomValue = random(0, 26);
    randomIdentifier[i] = randomValue + 'a';
  }
  Serial.printf("[CAP] Identifier: %s\n", randomIdentifier);
}

void generateCap(char* buffer, int buffer_size, statistic temp,
                 statistic humidity, statistic pressure, statistic light) {
  updateTime();

  Serial.println("[CAP] Compiling protocol XML.");
  snprintf(buffer, buffer_size, CAP_TEMPLATE, randomIdentifier,
           currentIdentifier++, formattedDate, randomIdentifier, temp.mean,
           temp.std, humidity.mean, humidity.std, pressure.mean, pressure.std,
           light.mean, light.std);
}
