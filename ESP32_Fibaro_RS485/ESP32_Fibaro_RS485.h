#ifndef RS485_FIBARO_ESP32_H
#define RS485_FIBARO_ESP32_H

#include "Constants.h"
#include "Utils.h"
#include <WiFi.h>
#include <WebServer.h>
#include "WiFIFunctions.h"
#include "ServerFunctions.h"


#define DEBUG_SERIAL    Serial
#define RS485_SERIAL    Serial2
#define ACTIVATE_DEBUG

#define RS485_CONTROL_PIN     33
#define WIFIOK_LED_PIN        26
#define SENDING_LED_PIN       27
extern WebServer server;

#endif