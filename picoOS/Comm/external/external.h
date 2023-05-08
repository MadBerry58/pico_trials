#ifndef COMM_INTERNAL_H
#define COMM_INTERNAL_H

#include <stdio.h>
#include "osMessages.h"

#define COMM_I2C
#define COMM_CAN

#define COMM_TYPE COMM_I2C

typedef enum 
{
    cortexController,
    lightSwitch,
    ledController,
    motorController
} NodeType_t;

#endif