#include "CAN_SM_APIs.h"
#include "../IPC/ipc.h"

///TODO: create interface for the following MCU variables
uint8_t frameNo     = 3u;
uint8_t rxStatus    = 0u;
uint8_t icStatus    = 0u;
bool    txReq       = 0u;

MCP2515_instance mainBus = 
{
    .RX_PIN         = 16u,
    .CS_PIN         = 17u,
    .SCK_PIN        = 18u,
    .TX_PIN         = 19u,
    .INT_PIN        = 20u,
    .SPI_CLOCK      = (20 * 1000 * 1000) /* 20 Mhz*/
};

can_frame broadcastFrame = 
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

can_frame RxBuffer;

static uint8_t framesLeft  = 0u;

void init_CAN_Hardware(void)
{
    MCP2515_init            (&(mainBus));
    MCP2515_reset           (&(mainBus));
    MCP2515_setBitrate      (&(mainBus), CAN_1000KBPS, MCP_20MHZ);
    MCP2515_setNormalMode   (&(mainBus));
    MCP2515_sendMessage     (&(mainBus), &(broadcastFrame));
}

/* RX Frame handler functionality */

void parseFrame(canIf_Rxframe *rxframe)
{
    uint64_t frameData = *(uint64_t*)(rxframe->canFrame.data);
    for(uint8_t i = 0u; i < rxframe->frameSignalNo; ++i)
    {
        void     *IPC_variable = (rxframe->IPC_variables[i].IPC_Variable);
        uint64_t  signalBits   = (frameData | ((1 << (rxframe->IPC_variables[i].bitSize)) - 1));

        switch(rxframe->IPC_variables[i].type)
        {
            case IPC_UINT64:
                *((uint64_t*)IPC_variable) = signalBits;
                break;

            case IPC_UINT32:
                *((uint32_t*)IPC_variable) = signalBits;
                break;

            case IPC_UINT16:
                *((uint16_t*)IPC_variable) = signalBits;
                break;

            case IPC_UINT8:
                *((uint8_t* )IPC_variable) = signalBits;
                break;

            case IPC_BOOL:
                *((bool*    )IPC_variable) = signalBits;
                break;

            default:
                printf("Unknown variable type");
        }

        // if(NULL != (rxframe->IPC_variables[i].signalCallback))
        // {
        //     SignalCallbacks[signalCallbackIndex] = rxframe->IPC_variables[i].signalCallback;
        //     ++signalCallbackIndex;
        // }

        frameData >>= (rxframe->IPC_variables[i].bitSize);
    }
}
void update_HW_data     (void)
{
    MCP2515_getStatus   (&(mainBus), &(icStatus));
    MCP2515_getRxStatus (&(mainBus), &(rxStatus));
}

bool framesReceived     (void)
{
    /* Read the RX status of the MCP2515 */
    return (0b00000000u < (RX_RXANY & rxStatus));
}

bool transmitRequired   (void)
{
    return txReq;
}

void receiveFrames()
{
    bool  loop = true;
    while(loop)
    {
        /* Check if any frame was received */
        {
            
            /* Read the data frame */
            MCP2515_readMessage(&(mainBus), &(RxBuffer));

            bool frameNotFound = true;
            /* Iterate through the known frame IDs array */
            for(uint8_t knownFrameIndex = 0; knownFrameIndex < frameNo; ++knownFrameIndex)
            {
                /* Check if the known frame ID matches the received frame ID */
                // if(CanIf_RxFrames[knownFrameIndex].canFrame.can_id == RxBuffer.can_id)
                // {
                //     /* Copy bitmapped data to local IPC variables */
                //     parseFrame(&(CanIf_RxFrames[knownFrameIndex]));
                //     frameNotFound = false;
                //     if(CanIf_RxFrames[knownFrameIndex].frameRxCallback != NULL)
                //     {
                //         SignalCallbacks[signalCallbackIndex] = CanIf_RxFrames[knownFrameIndex].frameRxCallback;
                //     }
                // }
            }

            /* If the received frame is not known, register the error and ignore the frame */
            if(true != frameNotFound)
            {
                //Register can filter error
                printf("Unknown frame received, ID: %d\n", RxBuffer.can_id);
            }
        // }
        // else
        // {
        //     loop = false;
        // }
    }

    // /* Process Rx frame callbacks */
    // for(frameCallbackIndex; frameCallbackIndex > 0u; --frameCallbackIndex)
    // {
    //     FrameCallbacks[frameCallbackIndex]();
    // }

    // /* Process Rx signal callbacks */
    // for(signalCallbackIndex; signalCallbackIndex > 0u; --signalCallbackIndex)
    // {
    //     (SignalCallbacks[signalCallbackIndex])();
    // }
    }
}

void sendFrames()
{
    bool    loop        = true;
    uint8_t TxStatus    = 0u;
    
    for(framesLeft; framesLeft > 0u; --framesLeft)
    {
        /* Read the TX status of the MCP2515 */
        MCP2515_getStatus(&(mainBus), &(TxStatus));

        if((TxStatus & TX_TXANY) == TX_TXANY)
        {
            // printf("Tx Buffers full\n");
            // if(0 < TxRetriesLeft)
            // {
            //     --TxRetriesLeft;
            //     continue;
            // }
            // else
            // {
            //     break;
            // }
        }
        else
        {
            
        }
        while(loop)
        {
            
        }
        // if(MCP2515_E_OK == MCP2515_sendMessage(&(mainBus), (can_frame*)&(TxFrames[updateFrameBuffer[i]]) ) )
        // {
        //     TxFrames[updateFrameBuffer[i]].updateFlag = false;
        //     TxFrames[updateFrameBuffer[i]].lastUpdate = time_us_32();
        //     TxFrames[updateFrameBuffer[i]].retryCount = 0u;
        // }
        // else
        // {
        //     /* Register a CAN controller issue */
        // }
    }
}