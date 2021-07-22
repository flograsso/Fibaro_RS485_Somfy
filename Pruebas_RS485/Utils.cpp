

#include "Utils.h"
#include "Constants.h"
#include "Pruebas_RS485.h"


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

      DEBUG_SERIAL.print("Ckecksum: ");
      DEBUG_SERIAL.println(checkSum,HEX);
      
      
      result[ACTION_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[ACTION_MSG_LENGTH - 1] = (uint8_t)checkSum;

      for (int i = 0; i < ACTION_MSG_LENGTH ;i++)
      {
            DEBUG_SERIAL.print("Complemento a 1: ");
            DEBUG_SERIAL.println(result[i],HEX);
      }

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

      DEBUG_SERIAL.print("Ckecksum: ");
      DEBUG_SERIAL.println(checkSum,HEX);

      result[PROG_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[PROG_MSG_LENGTH - 1] = (uint8_t)checkSum;

      for (int i = 0; i < PROG_MSG_LENGTH ;i++)
      {
            DEBUG_SERIAL.print("Complemento a 1: ");
            DEBUG_SERIAL.println(result[i],HEX);
      }
      
      return result;
}

uint8_t * makeGetChannelModePayload(uint8_t channel)
{
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

      DEBUG_SERIAL.print("Ckecksum: ");
      DEBUG_SERIAL.println(checkSum,HEX);

      result[PROG_MSG_LENGTH - 2] = (uint8_t)(checkSum >> 8);

      result[PROG_MSG_LENGTH - 1] = (uint8_t)checkSum;

      for (int i = 0; i < PROG_MSG_LENGTH ;i++)
      {
            DEBUG_SERIAL.print("Complemento a 1: ");
            DEBUG_SERIAL.println(result[i],HEX);
      }
      
      return result;
}


uint16_t getChecksum(uint8_t data[], uint8_t length)
{
      uint16_t sum = 0;
      for (int i = 0; i < length ; i++)  
      {
            sum += data[i];
            DEBUG_SERIAL.print("Suma parcial: ");
            DEBUG_SERIAL.println(data[i],HEX);
      }
        
      
      return sum;
}

