#include "Watchdog.h"
#include "hardware/watchdog.h"

uint8_t init_Watchdog()
{
    /* Initialize  */
    if (watchdog_caused_reboot()) 
    {
        ///OPTIMIZATION: check the reboot cause. in case of impactless soft reboot, skip writing configs to peripherals
        // printf("Rebooted by Watchdog!\n");
        ///TODO: parse error
    }
    else 
    {
        // printf("Clean boot\n");
    }
}

uint8_t setOSWatchdog()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t refreshOSWatchdog()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t setSubsystemWatchdog()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t refreshSubsystemWatchdog()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t registerScratchError()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t activateWatchdogDebugMode()
{
    uint8_t retVal = 0u;

    return retVal;
}