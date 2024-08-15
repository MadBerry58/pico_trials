#include "ipc.h"
#include "../../../picoOS_Types.h"

uint8_t ipc_Write(void *destination, void *source)
{
    uint8_t retVal = 0u;
    if(((CanIf_Signal*)destination)->type == ((CanIf_Signal*)source)->type)
    {
        
    }
    else
    {
        retVal = 1u;
    }

    return retVal;
}

/* Frames left to transmit */

