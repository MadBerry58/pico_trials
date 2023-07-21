#include "gpio.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

/* If debug mode is enabled, reserve default uart pins for debugger connection */
#ifdef DEBUG_PINS
//reserve pin 1 as UART_Serial
//reserve pin 2 as UART Serial
#endif