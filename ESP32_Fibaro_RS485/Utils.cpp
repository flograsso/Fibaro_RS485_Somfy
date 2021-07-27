

#include "Utils.h"
#include "Constants.h"
#include "ESP32_Fibaro_RS485.h"


uint8_t * makeActionPayload(uint8_t channel, char action)
{
      // El static es clave ya que "C++ does not advocate to return 
      // the address of a local variable to outside of the function 
      // so you would have to define the local variable as static variable."
      static uint8_t result[ACTION_MSG_LENGTH];
      uint16_t checkSum;

      result[MSG_POS] = ACTION_COMAND_CONTENT;
      result[LEN_POS] = ACTION_COMAND_LEN_CONTENT;
      result[RESERVED_POS] = RESERVED_CONTENT;

      // En orden inverso va el ID
      result[SOURCE_POS] = SORUCE_ID_POS_2;
      result[SOURCE_POS + 1] = SORUCE_ID_POS_1;
      result[SOURCE_POS + 2] = SORUCE_ID_POS_0;

      // En orden inverso va el ID
      result[DEST_POS] = RTS_ID_POS_2;
      result[DEST_POS + 1] = RTS_ID_POS_1;
      result[DEST_POS + 2] = RTS_ID_POS_0;

      result[DATA_POS] = channel;

      switch(action)
      {
            case 'U':
                  result[DATA_POS+1] = 0x01;
                  break;
            case 'D':
                  result[DATA_POS+1] = 0x02;
                  break;
            case 'S':
                  result[DATA_POS+1] = 0x03;
                  break;
            case 'F':
                  result[DATA_POS+1] = 0x04;
                  break;
      }

      for (int i = 0; i < DATA_POS + ACTION_MSG_DATA_LENGTH ;i++)
            result[i] = ~result[i];
      
      checkSum = getChecksum(result,DATA_POS + ACTION_MSG_DATA_LENGTH);


      
      
      result[ACTION_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[ACTION_MSG_LENGTH - 1] = (uint8_t)checkSum;

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.print("Comando enviado por RS485: ");
            for (int i = 0; i < ACTION_MSG_LENGTH ;i++)
            {
                  DEBUG_SERIAL.print(result[i],HEX);
                  DEBUG_SERIAL.print(" ");
            }
            DEBUG_SERIAL.println("");
      #endif

      return result;
}

uint8_t * makeProgPayload(uint8_t channel)
{

      // El static es clave ya que "C++ does not advocate to return 
      // the address of a local variable to outside of the function 
      // so you would have to define the local variable as static variable."
      static uint8_t result[PROG_MSG_LENGTH];
      uint16_t checkSum;

      result[MSG_POS] = PROG_COMAND_CONTENT;
      result[LEN_POS] = PROG_COMAND_LEN_CONTENT;
      result[RESERVED_POS] = RESERVED_CONTENT;

      // En orden inverso va el ID
      result[SOURCE_POS] = SORUCE_ID_POS_2;
      result[SOURCE_POS + 1] = SORUCE_ID_POS_1;
      result[SOURCE_POS + 2] = SORUCE_ID_POS_0;

      // En orden inverso va el ID
      result[DEST_POS] = RTS_ID_POS_2;
      result[DEST_POS + 1] = RTS_ID_POS_1;
      result[DEST_POS + 2] = RTS_ID_POS_0;

      result[DATA_POS] = channel;
      
      for (int i = 0; i < DATA_POS + PROG_MSG_DATA_LENGTH ;i++)
            result[i] = ~result[i];

      
      checkSum = getChecksum(result,DATA_POS + PROG_MSG_DATA_LENGTH);



      result[PROG_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[PROG_MSG_LENGTH - 1] = (uint8_t)checkSum;


      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.print("Comando enviado por RS485: ");
            for (int i = 0; i < PROG_MSG_LENGTH ;i++)
            {
                  DEBUG_SERIAL.print(result[i],HEX);
                  DEBUG_SERIAL.print(" ");
            }
            DEBUG_SERIAL.println("");
      #endif
      
      return result;
}


uint8_t * makeGetChannelModePayload(uint8_t channel)
{

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Comando de obtener data de CH en canal" + (String) channel);
      #endif
      // El static es clave ya que "C++ does not advocate to return 
      // the address of a local variable to outside of the function 
      // so you would have to define the local variable as static variable."
      static uint8_t result[PROG_MSG_LENGTH];
      uint16_t checkSum;

      result[MSG_POS] = GETCH_COMAND_CONTENT;
      result[LEN_POS] = GETCH_COMAND_LEN_CONTENT;
      result[RESERVED_POS] = RESERVED_CONTENT;

      // En orden inverso va el ID
      result[SOURCE_POS] = SORUCE_ID_POS_2;
      result[SOURCE_POS + 1] = SORUCE_ID_POS_1;
      result[SOURCE_POS + 2] = SORUCE_ID_POS_0;

      // En orden inverso va el ID
      result[DEST_POS] = RTS_ID_POS_2;
      result[DEST_POS + 1] = RTS_ID_POS_1;
      result[DEST_POS + 2] = RTS_ID_POS_0;

      result[DATA_POS] = channel;
      
      for (int i = 0; i < DATA_POS + PROG_MSG_DATA_LENGTH ;i++)
            result[i] = ~result[i];

      
      checkSum = getChecksum(result,DATA_POS + PROG_MSG_DATA_LENGTH);



      result[PROG_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[PROG_MSG_LENGTH - 1] = (uint8_t)checkSum;

      
      return result;
}


uint16_t getChecksum(uint8_t data[], uint8_t length)
{
      uint16_t sum = 0;
      for (int i = 0; i < length ; i++)  
      {
            sum += data[i];
      }
        
      
      return sum;
}


void sendGetChannelPayload(uint8_t channel)
{     
            
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Comando get channel mode cortina recibido. CH: " + (String)channel);
      #endif
      // Modo ENVIO
      digitalWrite(RS485_CONTROL_PIN, 1);
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Enviando");
      #endif

      uint8_t *result = makeGetChannelModePayload(channel);

      RS485_SERIAL.write("");
      for (int i = 0;i<PROG_MSG_LENGTH;i++)
      {
            RS485_SERIAL.write(result[i]);  
            delay(1);
      }
      RS485_SERIAL.write(""); //->>> LINEA CLAVE!!!!!!!!!!!!!!

      delay(110);

      // Modo recepcion
      digitalWrite(RS485_CONTROL_PIN, LOW);

      delay(1000);

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Esperando respuesta...");
            unsigned long time = millis();
            while(!RS485_SERIAL.available() && millis() - time > 6000);
            while(RS485_SERIAL.available())
            {     
                  DEBUG_SERIAL.print("HEX Leido: "); 
                  DEBUG_SERIAL.println(RS485_SERIAL.read(),HEX);       
            }
      #endif
      
}


void sendActionPayload(uint8_t channel, char action)
{     
            
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Comando Send Action recibido. Sobre CH: " + (String)channel);
            DEBUG_SERIAL.println("Accion: " + (String)action);
      #endif
      // Modo ENVIO
      digitalWrite(RS485_CONTROL_PIN, 1);
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Enviando");
      #endif

      uint8_t *result = makeActionPayload(channel,  action);

      RS485_SERIAL.write("");
      for (int i = 0;i<ACTION_MSG_LENGTH;i++)
      {
            RS485_SERIAL.write(result[i]);  
            delay(1);
      }
      RS485_SERIAL.write(""); //->>> LINEA CLAVE!!!!!!!!!!!!!!

      delay(110);

      // Modo recepcion
      digitalWrite(RS485_CONTROL_PIN, LOW);

      delay(1000);

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Esperando respuesta...");
            unsigned long time = millis();
            while(!RS485_SERIAL.available() && millis() - time > 6000);
            while(RS485_SERIAL.available())
            {     
                  DEBUG_SERIAL.print("HEX Leido: "); 
                  DEBUG_SERIAL.println(RS485_SERIAL.read(),HEX);       
            }
      #endif
      
}

void sendProgramPayload(uint8_t channel)
{     
            
       #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Comando PROG cortina recibido. CH: " + (String)channel);
      #endif
      // Modo ENVIO
      digitalWrite(RS485_CONTROL_PIN, 1);
      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Enviando");
      #endif

      uint8_t *result = makeProgPayload(channel);

      RS485_SERIAL.write("");
      for (int i = 0;i<PROG_MSG_LENGTH;i++)
      {
            RS485_SERIAL.write(result[i]);  
            delay(1);
      }
      RS485_SERIAL.write(""); //->>> LINEA CLAVE!!!!!!!!!!!!!!

      delay(110);

      // Modo recepcion
      digitalWrite(RS485_CONTROL_PIN, LOW);

      delay(1000);

      #ifdef ACTIVATE_DEBUG
            DEBUG_SERIAL.println("Esperando respuesta...");
            unsigned long time = millis();
            while(!RS485_SERIAL.available() && millis() - time > 6000);
            while(RS485_SERIAL.available())
            {     
                  DEBUG_SERIAL.print("HEX Leido: "); 
                  DEBUG_SERIAL.println(RS485_SERIAL.read(),HEX);       
            }
      #endif
      
}