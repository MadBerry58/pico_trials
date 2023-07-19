
#include "pico/multicore.h"
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

uint8_t init_OS(uint8_t nodeType, uint8_t nodeID)
{
    uint8_t error = 0u;


    /* Initialize OS modules */
    for(uint8_t i = 0u; i < init_routine_no; ++i)
    {
        if(error = OS_init_Routines[i]())
        {
            /* Handle init error */
        }
    }

    /* Establish communication with the network */
    network_connect(nodeType, nodeID);
}

/**
 * @brief picoOS core loop
 * 
 * 
 */
uint8_t run_OS()
{
    /* start watchdog */
    /* send start message to core 1 */
    /* check for core1 acknowledgement */
    
    /* enter OS loop */
    for(;;)
    {
        /*  */
    }
}

uint8_t init_nodeSM(uint8_t *nodeSM_initFunction())
{
    /* Init node SM using core 1 */
}

uint8_t run_nodeSM(uint8_t *nodeSM_runFunction())
{
    /* Run node SM */
}