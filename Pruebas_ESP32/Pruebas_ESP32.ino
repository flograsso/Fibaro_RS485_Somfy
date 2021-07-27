#include "Pruebas_ESP32.h"

/*
************************** IMPORTANTE!!!!!!!!!!!!!!!*********************
Al hacer el POST desde fibaro, el mismo debe terminar en "0x0D0x0A0x0D0x0A" ya que por default fibaro no envia CRLF
0x0D = FORM FEED (LF)   |  0x0A = LINE FEED (CR)

Ejemplo:

POST /cortina?CH=1&ACTION=U HTTP/1.10x0D0x0A0x0D0x0A
*/


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
      
}