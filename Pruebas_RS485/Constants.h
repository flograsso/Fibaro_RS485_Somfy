#ifndef CONSTANTS_H
#define CONSTANTS_H

// Posiciones
#define MSG_POS               0
#define LEN_POS               1
#define RESERVED_POS          2
#define SOURCE_POS            3
#define DEST_POS              6
#define DATA_POS              9



//Largos
#define MSG_LENGTH               1
#define LEN_LENGTH               1
#define RESERVED_LENGTH          1
#define SOURCE_LENGTH            3
#define DEST_LENGTH              3
#define PROG_MSG_LENGTH          12
#define ACTION_MSG_LENGTH        13
#define ACTION_MSG_DATA_LENGTH   2
#define PROG_MSG_DATA_LENGTH     1



// Contenido
#define RESERVED_CONTENT                  0x05
#define PROG_COMAND_CONTENT               0x97
#define PROG_COMAND_LEN_CONTENT           0x0C

#define ACTION_COMAND_CONTENT             0x80
#define ACTION_COMAND_LEN_CONTENT         0x0D

#define GETCH_COMAND_CONTENT             0xA0
#define GETCH_COMAND_LEN_CONTENT         0x0C

// ID del equipo RTS

#define RTS_ID_POS_0                0x05
#define RTS_ID_POS_1                0xDF
#define RTS_ID_POS_2                0xBD

// Test ID
/*
#define RTS_ID_POS_0                0x05
#define RTS_ID_POS_1                0x00
#define RTS_ID_POS_2                0x02
*/

// ID origen (entre FF FF 00 y FF FF FE)
#define SORUCE_ID_POS_0             0xFF
#define SORUCE_ID_POS_1             0xFF
#define SORUCE_ID_POS_2             0x00


#endif