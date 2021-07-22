#include "Pruebas_ESP32.h"




void setup()
{
      Serial.begin(9600);
      delay(3000);
      Serial.println("Iniciando....");
      ConnectWiFi_STA(true);
      InitServer();

}



void loop()
{
      server.handleClient();
      testWifiConnection();
      Serial.println("A");
}