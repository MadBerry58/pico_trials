#ifndef HARDWARE_H
#define HARDWARE_H

#include <stdio.h>

#include "dma/dma.h"
#include "interrupts/interrupts.h"
#include "memory/memory.h"
#include "peripherals/peripherals.h"
#include "pio/pio.h"

uint8_t init_Hardware();

uint8_t run_Hardware();

#endif