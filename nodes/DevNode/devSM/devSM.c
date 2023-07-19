#include "devSM.h"

#include "../../../picoOS/picoOS.h"



void run_devNodeSM()
{
    
}

uint8_t init_devNodeSM()
{
    uint8_t retVal = 0u;
    return retVal;
}

Task_t devSM_task = 
{
    .taskID         = 1u,
    .taskFunction   = NULL,
    .priority       = T_Prio_MODERATE,
    .cycleTime      = 5u,
    .nextTrigger    = 0u
};