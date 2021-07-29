
#ifndef NETWORK_DATA_H
#define NETWORK_DATA_H

#include <WiFi.h>

const char* ssid     = "DANTE";
const char* password = "0012963352";
const char* hostname = "ESP32_Fibaro";

IPAddress ip(192, 168, 68, 200);
IPAddress gateway(192, 168, 68, 1);
IPAddress subnet(255, 255, 255, 0);


#endif