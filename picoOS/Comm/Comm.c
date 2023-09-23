#include "Comm.h"
#include "hardware/irq.h"

#define NETWORK_CONNECT_TIMEOUT_MS 5000u /* 5 seconds to connect */

Errors_OS_e init_Comms()
{
    Errors_OS_e errorVal = OS_E_OK;
    CommSM_Error commSM_error = COMM_SM_E_OK;

    /* *****************************************
      Send Comm broadcast (Network ID + checksum)
       ***************************************** */

    /* initialize comm hw components */
    commSM_error = commSM_init();
    if(COMM_SM_E_OK != commSM_error)
    {
        uint16_t timeout;

        /* Start timer */

        while((timeout < NETWORK_CONNECT_TIMEOUT_MS) && (COMM_SM_E_OK == commSM_error))
        {
            commSM_run();
            /* check if network message is detected */
        }

        /* check if network is not available */
    }
    else
    {
        /*CommSM initialization failed */
    }


    
    /* bind software ports */
    /* test software ports */
    return errorVal;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t network_processMessages()
{
    uint8_t retVal = 0u;
    
    return retVal;
}

uint8_t network_send(uint8_t *message, uint8_t messageLength)
{
    uint8_t errorVal = 0u;
    /* Frame message into CAN frame */
    return errorVal;
}

uint8_t network_read(uint8_t *messageBuffer, uint8_t *messageSize)
{
    uint8_t errorVal = 0u;

    return errorVal;
}

uint8_t port_read()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t port_write()
{
    uint8_t retVal = 0u;

    return retVal;
}


