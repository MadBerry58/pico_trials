#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdio.h>

#include "../SystemServices/ErrorHandling/ErrorCodes.h"

#include "dma/dma.h"
#include "interrupts/interrupts.h"
#include "memory/memory.h"
#include "peripherals/peripherals.h"
#include "pio/pio.h"

///TODO: add hardware configuration template
/* 
typedef struct {
    dmaConfig;
    peripheralConfig;
    pioConfig;
    interruptConfig;
    sioConfig; 
} Hardware_config;
 */

Errors_OS_e init_Hardware();

Errors_OS_e run_Hardware();

#endif