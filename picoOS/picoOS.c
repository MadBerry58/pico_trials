
#include "picoOS.h"

uint8_t (*OS_init_Routines[])(void) = 
{
    init_Watchdog,
    init_Hardware,
    init_Comms,
    init_PinControl,
    init_Timers,
    init_OS_scheduler
};

uint8_t init_routine_no = sizeof(OS_init_Routines) / sizeof(OS_init_Routines[0]);

void init_OS()
{
    uint8_t error = 0u;
    // stdio_init_all();
    for(uint8_t i = 0u; i < init_routine_no; ++i)
    {
        if(error = OS_init_Routines[i]())
        {
            /* Handle init error */
        }
    }
}

/**
 * @brief picoOS core loop
 * 
 * 
 */
void run_OS()
{
    /* start watchdog */
    /* send start message to core 1 */
    /* check for core1 acknowledgement */
    
    /* enter OS loop */
}