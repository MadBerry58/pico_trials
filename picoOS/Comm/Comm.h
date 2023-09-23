#ifndef COMM_H
#define COMM_H

#include <stdio.h>
#include "pico/stdlib.h"

#include "../SystemServices/ErrorHandling/ErrorCodes.h"
#include "commSM/commSM.h"
#include "Address_Masks.h"


Errors_OS_e init_Comms  ();

/* Area network interfaces */
bool    network_connected();

uint8_t network_connect (uint8_t  nodeType,      uint8_t  nodeID);
uint8_t network_send    (uint8_t *message,       uint8_t  messageLength);
uint8_t network_read    (uint8_t *messageBuffer, uint8_t *messageSize);

/* Internal communication interfaces */
uint8_t port_read       ();
uint8_t port_write      ();

#endif