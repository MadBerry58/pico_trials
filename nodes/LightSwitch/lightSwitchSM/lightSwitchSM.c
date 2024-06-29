#include "lightSwitchSM.h"

#include "nodeSWC/controlLogic/controlLogic.h"
#include "nodeSWC/encoderSM/encoderSM.h"
#include "nodeSWC/pushButtonSM/pushButtonSM.h"

void core_lightSwitchSM(void)
{
    /* Confirm core FIFO functionality */
    /* Initialize SWCs */
    init_encoderSM_swc();
    init_pushButtonSM ();
    /* Run scheduler SWCs */
    while(1)
    {
        run_encoderSM_swc();
        run_pushButtonSM();

    }
}