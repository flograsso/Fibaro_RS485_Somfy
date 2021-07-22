
#include "Pruebas_RS485.h"

void setup()
{          
      DEBUG_SERIAL.begin(9600);
 
      delay(3000);
      DEBUG_SERIAL.println("Init");
      
      // 8 bits de datos. 1 bit de parada. Paridad odd
      RS485_SERIAL.begin(4800,SERIAL_8O1);

      //RS485_SERIAL.begin(9600);
      
      RS485_SERIAL.setTimeout(100);

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
      
      digitalWrite(RS485_CONTROL_PIN, HIGH);
      delay(4000);
      DEBUG_SERIAL.println("Enviando");
      uint8_t *result = makeProgPayload(1);

      


      for (int i = 0;i<PROG_MSG_LENGTH;i++)
     {
            //RS485_SERIAL.print(result[i],HEX);
            //String b =String(result[i],HEX);
            RS485_SERIAL.write(result[i]);  


     }

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
      delay(4000);

      DEBUG_SERIAL.println("Esperando rta x 1min");
      unsigned long time = millis();
      while(!RS485_SERIAL.available() && millis() - time > 60000);


      while(RS485_SERIAL.available())
      {
            DEBUG_SERIAL.println(RS485_SERIAL.read());        
      }
      delay(3000);
}


