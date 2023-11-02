#include "Comm.h"
#include "hardware/irq.h"

#include "../Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"

#define NETWORK_CONNECT_TIMEOUT_MS 5000u /* 5 seconds to connect */
MCP2515_instance mainBus = 
{
    .RX_PIN         = 16u,
    .CS_PIN         = 17u,
    .SCK_PIN        = 18u,
    .TX_PIN         = 19u,
    .INT_PIN        = 20u,
    .SPI_CLOCK      = (10 * 1000 * 1000) /* 8 Mhz*/
};

can_frame dummyFrame = 
{
    .can_id     = 167u,
    .can_dlc    = 4u,
    .data       = 
    {
        29u,
        23u,
        19u,
        17u
    }
};

Errors_OS_e init_Comms()
{
    Errors_OS_e errorVal = OS_E_OK;
    CommSM_Error commSM_error = COMM_SM_E_OK;

    /* *****************************************
      Send Comm broadcast (Network ID + checksum)
       ***************************************** */

    /* initialize comm hw components */
    commSM_error = commSM_init();
    if(COMM_SM_E_OK == commSM_error)
    {
        // uint16_t timeout;

        MCP2515_init            (&(mainBus));
        MCP2515_reset           (&(mainBus));
        MCP2515_setBitrate      (&(mainBus), CAN_125KBPS, MCP_8MHZ);
        MCP2515_setNormalMode   (&(mainBus));
        
        MCP2515_sendMessage     (&(mainBus), &(dummyFrame));
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
    MCP2515_Error readStatus = MCP2515_readMessage(&(mainBus), &(dummyFrame));
    if(MCP2515_E_NOMSG == readStatus)
    {

    }
    else
    if(MCP2515_E_UNKNOWN == readStatus)
    {

    }
    else
    {/* message received */
        
        printf("CAN frame ID:  %lu \n", dummyFrame.can_id);
        printf("CAN frame DLC: %lu \n", dummyFrame.can_dlc);
        for(int i = 0; i < dummyFrame.can_dlc; ++i)
            printf("CAN frame byte %d:  %lu \n", i, dummyFrame.data[i]);
        
    }

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


