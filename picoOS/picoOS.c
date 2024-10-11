#include "picoOS.h"

/* Required functionality init */
Errors_OS_e (*OS_init_Routines[])(void) = 
{
    // init_Watchdog,
    init_Hardware,      //hardware needs to be initialized before board can be used
    init_Timers,        //timer functionality required for following components

    // init_Comms,         //connection to required for enabling network functionality
};

/* Required functionality init */
Errors_OS_e (*OS_main_Routines[])(void) = 
{
    // refresh_Watchdog,
    // read_system_measurements,
    // handle_messages

};


uint8_t init_routine_no = sizeof(OS_init_Routines) / sizeof(OS_init_Routines[0]);

uint8_t init_OS(uint8_t nodeType, uint8_t nodeID)
{
    uint8_t retVal = 0u;
    stdio_init_all();
    // init_Comms();
    /* Initialize OS modules */
    /* Establish communication with the network */
    // network_connect(nodeType, nodeID);
    // printf("OS initialized\n");
    return retVal;
}

/**
 * @brief picoOS core loop
 * 
 * 
 */
uint8_t run_OS()
{
    uint8_t retVal = 0u;
    /* start watchdog */
    /* send start message to core 1 */
    /* check for core1 acknowledgement */
    /* enter OS loop */
    printf("OS STARTED\n");
    for(;;)
    {
        /*  */
    }
    return retVal;
}