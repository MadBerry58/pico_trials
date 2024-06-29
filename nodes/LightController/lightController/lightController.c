#include "lightController.h"

#include "nodeSWC/coldLedSM/coldLedSM.h"
#include "nodeSWC/warmLedSM/warmLedSM.h"
#include "nodeSWC/rgbSM/rgbSM.h"
#include "nodeSWC/controlLogic/controlLogic.h"

/* IPC variables */

void core_lightControllerSM(void)
{
    /* Confirm core FIFO functionality */

    /* Initialize SWCs */
    controlLogic_Init   ();
    warmLedSM_Init      ();
    coldLedSM_Init      ();
    rgmSM_Init          ();


    /* Run scheduler SWCs */
    controlLogic_Run    ();

    warmLedSM_Run       ();
    rgmSM_Run           ();
    coldLedSM_Run       ();
}