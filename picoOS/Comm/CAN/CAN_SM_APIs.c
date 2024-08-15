#include "CAN_SM_APIs.h"
// #include "../IPC/ipc.h"
#include "../../picoOS_Types.h"

#include <string.h>

///TODO: create interface for the following MCU variables

can_frame RxBuffer;

/* ***  Helper functions  *** */
void decodeFrame         (CanIf_Frame *rxframe)
{
    uint64_t frameData = *(uint64_t*)(rxframe->canFrame.data);
    
    for(uint8_t i = 0u; i < rxframe->signalNo; ++i)
    {
        uint64_t  signalBits   = (frameData | ((1 << (rxframe->signals[i].bitSize)) - 1));

        switch(rxframe->signals[i].type)
        {
            case IPC_UINT64:
                rxframe->signals[i].ipcData.uint64Data    = (uint64_t)signalBits;
                break;

            case IPC_UINT32:
                rxframe->signals[i].ipcData.uint64Data    = (uint32_t)signalBits;
                break;

            case IPC_UINT16:
                rxframe->signals[i].ipcData.uint16Data    = (uint16_t)signalBits;
                break;

            case IPC_UINT8:
                rxframe->signals[i].ipcData.uint8Data     = (uint8_t) signalBits;
                break;

            case IPC_BOOL:
                rxframe->signals[i].ipcData.booleanData   = (bool)    signalBits;
                break;

            default:
                printf("Unknown variable type");
        }

        if(NULL != (rxframe->signals[i].updateCallback))
        {
            (rxframe->signals[i].updateCallback)();
        }

        frameData >>= (rxframe->signals[i].bitSize);
    }
}

// void encodeFrame         (CanIf_frame *txframe)
// {
//     uint64_t frameData = *(uint64_t*)(rxframe->canFrame.data);
    
//     for(uint8_t i = 0u; i < rxframe->frameSignalNo; ++i)
//     {
//         uint64_t  signalBits   = (frameData | ((1 << (rxframe->IPC_variables[i].bitSize)) - 1));

//         switch(rxframe->IPC_variables[i].type)
//         {
//             case IPC_UINT64:
//                 rxframe->IPC_variables[i].ipcData.uint64Data    = (uint64_t)signalBits;
//                 break;

//             case IPC_UINT32:
//                 rxframe->IPC_variables[i].ipcData.uint64Data    = (uint32_t)signalBits;
//                 break;

//             case IPC_UINT16:
//                 rxframe->IPC_variables[i].ipcData.uint16Data    = (uint16_t)signalBits;
//                 break;

//             case IPC_UINT8:
//                 rxframe->IPC_variables[i].ipcData.uint8Data     = (uint8_t) signalBits;
//                 break;

//             case IPC_BOOL:
//                 rxframe->IPC_variables[i].ipcData.booleanData   = (bool)    signalBits;
//                 break;

//             default:
//                 printf("Unknown variable type");
//         }

//         if(NULL != (rxframe->IPC_variables[i].updateCallback))
//         {
//             (rxframe->IPC_variables[i].updateCallback)();
//         }

//         frameData >>= (rxframe->IPC_variables[i].bitSize);
//     }
// }

/*** SM Actions ***/
void init_CAN_Hardware  (CanIf_t *canInterface)
{
    MCP2515_init            (&(canInterface->canBusCfg));
    MCP2515_reset           (&(canInterface->canBusCfg));
    MCP2515_setBitrate      (&(canInterface->canBusCfg), CAN_1000KBPS, MCP_8MHZ);
    MCP2515_setNormalMode   (&(canInterface->canBusCfg));
}

void update_HW_data     (CanIf_t *canInterface)
{
    MCP2515_getStatus   (&(canInterface->canBusCfg), &(canInterface->canBusCfg.icStatus));
    MCP2515_getRxStatus (&(canInterface->canBusCfg), &(canInterface->canBusCfg.rxStatus));
}

void receiveFrames      (CanIf_t *canInterface)
{
    /* Read the data frame */
    MCP2515_readMessage(&(canInterface->canBusCfg), &(RxBuffer));

    /* Iterate through the known frame IDs array */
    for(uint8_t knownFrameIndex = 0; knownFrameIndex < canInterface->rxIfFrame_no; ++knownFrameIndex)
    {
        /* Check if the known frame ID matches the received frame ID */
        if(canInterface->rxIfFrames[knownFrameIndex].canFrame.can_id == RxBuffer.can_id)
        {
            memcpy(canInterface->rxIfFrames[knownFrameIndex].canFrame.data, RxBuffer.data, canInterface->rxIfFrames[knownFrameIndex].canFrame.can_dlc);
            canInterface->rxIfFrames[knownFrameIndex].frameUpdated = true;
        }
        else
        {
            //Register can filter error
            printf("Unknown frame received, ID: %d\n", RxBuffer.can_id);
        }
    }
}

void processRxFrames    (CanIf_t *canInterface)
{
    /* Process Rx frame callbacks */
    for(uint8_t frameCallbackIndex = 0u; frameCallbackIndex < canInterface->rxIfFrame_no; ++frameCallbackIndex)
    {
        if( 
            (NULL != canInterface->rxIfFrames[frameCallbackIndex].frameUpdateCallback) &&
            (true == canInterface->rxIfFrames[frameCallbackIndex].frameUpdated)
        )
        {
            (canInterface->rxIfFrames[frameCallbackIndex].frameUpdateCallback)();
        }
        else
        {
            
        }

        decodeFrame(&(canInterface->rxIfFrames[frameCallbackIndex]));
    }
}

void transmitFrames     (CanIf_t *canInterface)
{
    uint8_t TxStatus    = 0u;
    uint8_t frameIndex  = 0u;
    
    for(frameIndex = 0; frameIndex < canInterface->txIfFrame_no; ++frameIndex)
    {
        /* Read the TX status of the MCP2515 */
        MCP2515_getStatus(&(canInterface->canBusCfg), &(TxStatus));

        /* Check if any TX buffer is available */
        if((TxStatus & TX_TXANY) == TX_TXANY)
        {
            /* Check if retries are available for frame */
            if(0 < canInterface->txIfFrames[frameIndex].retriesLeft)
            {
                --(canInterface->txIfFrames[frameIndex].retriesLeft);


                MCP2515_sendMessage(&(canInterface->canBusCfg), &(canInterface->txIfFrames[frameIndex].canFrame));

                /* Reset the retry counter */
                canInterface->txIfFrames[frameIndex].retriesLeft = canInterface->txIfFrames[frameIndex].updateRetries;
            }
            else
            {
                /* Report error */
            }
        }
        else
        {
            
        }
    }
}

/*** Transition Checks ***/
bool framesReceived     (CanIf_t *canInterface)
{
    /* Read the RX status of the MCP2515 */
    return (0b00000000u < (RX_RXANY & canInterface->canBusCfg.rxStatus));
}

bool transmitRequired   (CanIf_t *canInterface)
{
    uint8_t frameIndex = 0;
    uint16_t txReq = 0u;
    for(frameIndex = 0u; frameIndex < canInterface->txIfFrame_no; ++frameIndex)
    {
        if(true == canInterface->txIfFrames[frameIndex].frameUpdated)
        {
            txReq |= 1 << frameIndex;
        }
        else
        {
            txReq ^= 1 << frameIndex;
        }
    }
    return txReq;
}