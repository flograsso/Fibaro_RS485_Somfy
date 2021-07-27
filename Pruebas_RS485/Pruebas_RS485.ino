
#include "Pruebas_RS485.h"

void setup()
{          

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.begin(9600);
            delay(3000);
            DEBUG_SERIAL.println("Init");
      #endif
            RS485_SERIAL.begin(4800,SERIAL_8O1);

      RS485_SERIAL.setTimeout(1000);

      //Transmisor mode
      pinMode(RS485_CONTROL_PIN,OUTPUT);



      /*
      delay(4000);
      DEBUG_SERIAL.println("Init...");
      uint8_t *result = makeActionPayload(4,'D');
      DEBUG_SERIAL.println("Resultado final");
      for (int i = 0;i<ACTION_MSG_LENGTH;i++)
            DEBUG_SERIAL.println(*(result+i),HEX);
      */

}

void loop()
{
      
      // Modo ENVIO
      digitalWrite(RS485_CONTROL_PIN, HIGH);
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Enviando");
      #endif
      //uint8_t *result = makeGetChannelModePayload(1);

      //5F f3 fa ff 0 0 42 20 fa fe 5 a5
      byte vector[] = {0x5F, 0xf3 ,0xfa ,0xff ,0x0 ,0x0 ,0x42 ,0x20 ,0xfa ,0xfe ,0x05 ,0xa5};
      //RS485_SERIAL.write(vector,sizeof(vector));
      RS485_SERIAL.write("");
      for (int i = 0;i<PROG_MSG_LENGTH;i++)
     {
            //RS485_SERIAL.print(result[i],HEX);
            //String b =String(result[i],HEX);
            RS485_SERIAL.write(vector[i]);  
            delay(1);
            //digitalWrite(ONBOARD_LED, !digitalRead(ONBOARD_LED));
     }
     RS485_SERIAL.write(""); //->>> LINEA CLAVE!!!!!!!!!!!!!!
       
      for (int i = 0; i < PROG_MSG_LENGTH ;i++)
      {
            DEBUG_SERIAL.print("Complemento a 1: ");
            DEBUG_SERIAL.println(vector[i],HEX);
      }
      // Modo recepcion
      digitalWrite(RS485_CONTROL_PIN, LOW); 

      



     

      /*
      String deveui="";

      for(int i = 0; i < PROG_MSG_LENGTH; i++)
            {     
                 
                  if(result[i] > 0x0F)
                  {
                         // Si el HEX tiene dos dígitos lo concateno
                        deveui = deveui + String(result[i],HEX);
                  }
                  else
                        {
                               // Si el HEX tiene solo 1 dígito, le agrego un "0" antes.
                              deveui = deveui + "0";
                              deveui = deveui + String(result[i],HEX);
                        }
            }
      
          */  
      //RS485_SERIAL.print(deveui);
      DEBUG_SERIAL.println("Enviado");
      delay(1000);
      //Receptor mode
      digitalWrite(RS485_CONTROL_PIN, LOW); 
      //delay(4000);

      DEBUG_SERIAL.println("Esperando rta x 1min");
      unsigned long time = millis();
      while(!RS485_SERIAL.available() && millis() - time > 60000);


      while(RS485_SERIAL.available())
      {     
            DEBUG_SERIAL.println("Lei:"); 
            DEBUG_SERIAL.print(RS485_SERIAL.read(),HEX);        
      }

      delay(3000);
}
