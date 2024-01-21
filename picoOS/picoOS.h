#ifndef PICO_OS_H
#define PICO_OS_H

#define MAX_EVENTS 256u
#define MAX_TASKS  32u

#include <stdlib.h>
#include <stdio.h>
#include "Comm/Comm.h"
#include "FlashControl/FlashControl.h"
#include "Hardware/Hardware.h"
#include "Scheduler/Scheduler.h"
#include "SystemServices/ErrorHandling/ErrorHandling.h"
#include "SystemServices/Timers/Timers.h"
#include "SystemServices/Watchdog/Watchdog.h"

uint8_t init_OS(uint8_t nodeType, uint8_t nodeID);
uint8_t run_OS();

/* Supported node types */
typedef enum
{
    Development,
    LightController,
    LightSwitch,
    RadiatorController,
    WindowController,
    LedTester
    
} NodeType_e;

#endif