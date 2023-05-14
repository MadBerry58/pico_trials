#ifndef PICO_OS_H
#define PICO_OS_H

/* OS definitions */
#define MAX_TASKS  32u
#define MAX_EVENTS 64u

#include <stdlib.h>
#include <stdio.h>
#include "Comm/Comm.h"
#include "ErrorHandling/ErrorHandling.h"
#include "FlashControl/FlashControl.h"
#include "Hardware/Hardware.h"
#include "PinControl/PinControl.h"
#include "Scheduler/Scheduler.h"
#include "Timers/Timers.h"
#include "Watchdog/Watchdog.h"

uint8_t init_OS();
uint8_t run_OS();

uint8_t init_nodeSM(uint8_t *nodeSM_initFunction());
uint8_t run_nodeSM(uint8_t *nodeSM_runFunction());

#endif