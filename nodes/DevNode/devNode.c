#include "devSM/devSM.h"
#include "../../picoOS/picoOS.h"

#define nodeInitScheduleTasks 10u
#define nodeRunScheduleTasks 10u

uint8_t (*nodeInitSchedule[nodeInitScheduleTasks])() = 
{
    init_devNodeSM
};

uint8_t (*nodeRunSchedule[nodeRunScheduleTasks])() = 
{
    run_devNodeSM
};

void main()
{
    /* Initialize base OS functionality */
    if(init_OS())
    {
        /* Handle initialization error */
    }

    /* Initialize node-specific functionality on core 1 */
    if(init_devNodeSM())
    {
        /* Initialize node software components */
    }

    /* Prime the node scheduler loop to wait for core 0 signal */
    run_devNodeSM();

    uint8_t error = 0u;
    /* Start the OS and trigger the node scheduler loop */
    while(0u == error)
    {
        error = run_OS();
        if(error)
        {
            /* handle OS error */
        }

    }

    
}