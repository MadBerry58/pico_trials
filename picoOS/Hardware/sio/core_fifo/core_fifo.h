#ifndef CORE_FIFO_H
#define CORE_FIFO_H
#include <stdio.h>

typedef struct 
{
    uint16_t message;
    uint8_t  messageIndex;
    uint8_t  messageType;
    uint8_t  messagePriority;
} core_FIFO_message;

uint8_t sendMessage(core_FIFO_message *messageBuffer, uint8_t messageNumber);

uint8_t receiveMessage(core_FIFO_message *messageBuffer);

#endif