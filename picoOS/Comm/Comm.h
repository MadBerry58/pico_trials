#ifndef COMM_H
#define COMM_H

#include <stdio.h>
#include "Adresses.h"

uint8_t frame_send();
uint8_t frame_read();

uint8_t port_read();
uint8_t port_write();

#endif