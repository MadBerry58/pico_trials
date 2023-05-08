#ifndef COMM_H
#define COMM_H

#include <stdio.h>
#include "Adresses.h"

uint8_t init_Comms();

uint8_t network_send(uint8_t *message,       uint8_t  messageLength);
uint8_t network_read(uint8_t *messageBuffer, uint8_t *messageSize);

uint8_t port_read();
uint8_t port_write();

#endif