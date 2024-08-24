#include "ipc.h"
#include "../../picoOS_Types.h"

typedef struct
{
    IpcContainer      ipcData;              // IPC variable containing the signal data
    void      (*updateCallback)();    // the function called when the signal data update is handled
} IpcVariable;

uint8_t ipc_Write(CanIf_Signal *destination, void *source, uint8_t source_bitSize)
{
  ///TODO: as the destination frame already knows what data it wants, use that instead of logical checks
    uint8_t retVal = 0u;
    if((destination)->type == ((CanIf_Signal*)source)->type)
    {

    }
    else
    {
        retVal = 1u;
    }

    return retVal;
}

/* Frames left to transmit */

