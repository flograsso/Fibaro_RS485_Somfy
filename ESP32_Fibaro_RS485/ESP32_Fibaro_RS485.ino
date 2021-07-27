#include "ESP32_Fibaro_RS485.h"



/*
************************** IMPORTANTE!!!!!!!!!!!!!!!*********************
Al hacer el POST desde fibaro, el mismo debe terminar en "0x0D0x0A0x0D0x0A" ya que por default fibaro no envia CRLF
0x0D = FORM FEED (LF)   |  0x0A = LINE FEED (CR)

Ejemplo:

POST /cortina?CH=1&ACTION=U HTTP/1.10x0D0x0A0x0D0x0A
*/

#define ACTIVATE_DEBUG


void setup()
{

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.begin(9600);
            delay(3000);
            DEBUG_SERIAL.println("Init");
      #endif
      initSerialRS485();

      ConnectWiFi_STA(true);
      InitServer();
      

}



void loop()
{
      server.handleClient();
      testWifiConnection();
     
      
}





void initSerialRS485()
{
      // 8 bits de datos. 1 bit de parada. Paridad odd
      RS485_SERIAL.begin(4800,SERIAL_8O1);

      RS485_SERIAL.setTimeout(100);

      //Transmisor mode
      pinMode(RS485_CONTROL_PIN,OUTPUT);
}