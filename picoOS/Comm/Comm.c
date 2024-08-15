#include "Comm.h"
#include "hardware/irq.h"

#include "CAN/CAN_SM.h"
#include "IPC/ipc.h"
#include "../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"

#define NETWORK_CONNECT_TIMEOUT_MS 5000u /* 5 seconds to connect */

Errors_OS_e init_Comms(CanIf_t *canInterface)
{
    Errors_OS_e errorVal = OS_E_OK;
    CommSM_Error commSM_error = COMM_SM_E_OK;

    CAN_SM_init(canInterface);

    if(COMM_SM_E_OK == commSM_error)
    {

    }
    else
    {
        /*CommSM initialization failed */
    }
    return errorVal;
}