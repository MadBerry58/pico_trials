#ifndef TIMERS_H
#define TIMERS_H

#include <stdio.h>

uint8_t init_Timers();

uint8_t check_timer(uint32_t *timerVariable, uint32_t timeoutVal);

uint8_t start_timer(uint32_t *timerVariable);


#endif