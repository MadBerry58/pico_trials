#include "Comm.h"
#include "hardware/irq.h"

uint8_t init_Comms()
{
    uint8_t errorVal = 0u;

    //Send Comm broadcast (Network ID + checksum)
    
    /* initialize comm hw components */
    /* bind software ports */
    /* test software ports */

    //Check for response
        //Handle errors
    //check if the data frames are up to date
    return errorVal;
}

uint8_t network_connect(uint8_t nodeType,       uint8_t nodeID)
{
    uint8_t retVal = 0u;
    

    return retVal;
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


