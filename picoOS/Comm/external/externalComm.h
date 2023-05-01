#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define COMM_I2C
#define COMM_CAN

#define COMM_TYPE COMM_I2C

enum NodeType_t
{
    cortexController,
    lightSwitch,
    ledController,
    motorController
}