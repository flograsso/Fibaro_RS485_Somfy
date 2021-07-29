#ifndef UTILS_H
#define UTILS_H

#include "Arduino.h"


uint16_t getChecksum(uint8_t * data, uint8_t length);
uint8_t * makeProgPayload(uint8_t channel);
uint8_t * makeActionPayload(uint8_t channel, char action);
uint8_t * makeGetChannelModePayload(uint8_t channel);
void sendActionPayload(uint8_t channel, char action);
void sendProgramPayload(uint8_t channel);
void sendGetChannelPayload(uint8_t channel);
void ledBlink(byte pin);


#endif