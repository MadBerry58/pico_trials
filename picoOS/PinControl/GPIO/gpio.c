#include "gpio.h"
#include <stdio.h>



/* Useless wrapper around the set gpio sdk for the sake of consistency */
uint8_t setPin(uint8_t gpioNo, bool state, uint8_t refreshTime)
{

    return 0u;
}

uint8_t writeMultiPinBus(uint32_t data, uint32_t dataMask)
{
    
    return 0u;
}