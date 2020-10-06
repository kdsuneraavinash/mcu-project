#include <stdio.h>

#include "sensor.h"

/**
 * Template for cap message.
 *
 * Parameters (in order):
 *      identifier(str)
 *      sent(str)
 *      params
 **/
const char* CAP_TEMPLATE =
    "<?xml version = \"1.0\" encoding = \"UTF-8\"?>"
    "<alert xmlns = \"urn:oasis:names:tc:emergency:cap:1.2\">"
    "<identifier>%s</identifier>"
    "<sender>device</sender>"
    "<sent>%s</sent>"
    "<status>Actual</status>"
    "<msgType>Alert</msgType>"
    "<scope>Private</scope>"
    "<info>"
    "<category>Env</category>"
    "<event>SENSOR_DATA</event>"
    "<responseType>None</responseType> "
    "<urgency>Unknown</urgency>"
    "<severity>Minor</severity>"
    "<certainty>Observed</certainty>"
    "<senderName>MCU_DEVICE</senderName>"
    "<parameter>"
    "<valueName>TEMP_MEAN</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>TEMP_STD</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>HUMIDITY_MEAN</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>HUMIDITY_STD</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>PRESSURE_MEAN</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>PRESSURE_STD</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>LIGHT_MEAN</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "<parameter>"
    "<valueName>LIGHT_STD</valueName>"
    "<value>%f</value>"
    "</parameter>"
    "</info>"
    "</alert>";

void generateCap(char* buffer, int buffer_size, sensor temp, sensor humidity,
                 sensor pressure, sensor light) {
  char identifier[] = "name";
  char sent[] = "2008-11-19T14:57:00-07:00";
  snprintf(buffer, buffer_size, CAP_TEMPLATE, identifier, sent, temp.mean,
           temp.std, humidity.mean, humidity.std, pressure.mean, pressure.std,
           light.mean, light.std);
}
