#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <stdio.h>

uint8_t init_Interrupts();

uint8_t enable_interrupt();

uint8_t disable_interrupt();

uint8_t set_interruptHandler();

#endif