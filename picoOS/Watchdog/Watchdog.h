#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdio.h>

uint8_t init_Watchdog();

uint8_t setOSWatchdog();
uint8_t refreshOSWatchdog();

uint8_t setSubsystemWatchdog();
uint8_t refreshSubsystemWatchdog();

uint8_t registerScratchError();

uint8_t activateWatchdogDebugMode();

#endif