#include "CAN_SM_APIs.h"
// #include "../IPC/ipc.h"
#include "../../picoOS_Types.h"

#include <string.h>

///TODO: create interface for the following MCU variables

can_frame RxBuffer;
/* ***  Helper functions  *** */
void decodeFrame                (CanIf_Frame *rxFrame);
void encodeFrame                (CanIf_Frame *txFrame);
void attemptFrameTransmission   (CanIf_t *canInterface, uint8_t frameIndex);


/********************* SM Actions *********************/

/**
 * @brief Initialize the CAN Hardware Controller
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void init_CAN_Hardware  (CanIf_t *canInterface)
{
    MCP2515_init            (&(canInterface->canBusCfg));
    MCP2515_reset           (&(canInterface->canBusCfg));
    MCP2515_setBitrate      (&(canInterface->canBusCfg), CAN_500KBPS, MCP_8MHZ);
    MCP2515_setNormalMode   (&(canInterface->canBusCfg));
    MCP2515_sendMessage     (&(canInterface->canBusCfg), &(canInterface->txIfFrames[0].canFrame));
}


/**
 * @brief Read the Tx and Rx status
 * @details Read the status bytes from the CAN IC and save them to the interface status containers 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void update_HW_data     (CanIf_t *canInterface)
{
    MCP2515_getStatus       (&(canInterface->canBusCfg), &(canInterface->canBusCfg.icStatus));
    MCP2515_getRxStatus     (&(canInterface->canBusCfg), &(canInterface->canBusCfg.rxStatus));
}


/**
 * @brief Read the received frames
 * @details Read the known frame bytes from the CAN IC and write it to the respective buffers
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void receiveFrames      (CanIf_t *canInterface)
{
    uint8_t knownFrameIndex = 0u;

    /* Read the data frame */
    MCP2515_readMessage(&(canInterface->canBusCfg), &(RxBuffer));

    /* Iterate through the known frame IDs array */
    for(knownFrameIndex = 0u; knownFrameIndex < (canInterface->rxIfFrame_no); ++knownFrameIndex)
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


/**
 * @brief Process the signals contained in the received frames
 * @details Transfer the data from the local frame buffers to the specific signal containers
 *          Register all the required signal update triggers
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void processRxFrames    (CanIf_t *canInterface)
{
    /* Process Rx frame callbacks */
    for(uint8_t frameCallbackIndex = 0u; frameCallbackIndex < canInterface->rxIfFrame_no; ++frameCallbackIndex)
    {
        if(
            /*  */
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


/**
 * @brief Process the signals contained in the transmit frames
 * @details Parse the data from the signal containers into the transmit frame buffer
 *          Register all the required frame transmit requests
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void processTxFrames    (CanIf_t *canInterface)
{
    /* Check containers for set update flags */

    /* Offset and scale the signal */

    /* Clean the signal memory area and write the new signal data */

    /* Check if the frame is cyclic or send-on-update (send on request sets the flags separately) */

}


/**
 * @brief 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return * void 
 */
void transmitFrames     (CanIf_t *canInterface)
{
    uint8_t frameIndex  = 0u;
    
    for(frameIndex = 0; frameIndex < canInterface->txIfFrame_no; ++frameIndex)
    {
        /* Check the Transmit_Required flag */
        if(true == canInterface->txIfFrames[frameIndex].transmitRequired)
        {
            attemptFrameTransmission(canInterface, frameIndex);
        }
    }
}


/*** Transition Checks ***/

/**
 * @brief 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return true 
 * @return false 
 */
bool framesReceived     (CanIf_t *canInterface)
{
    /* Read the RX status of the MCP2515 */
    return (0b00000000u < (RX_RXANY & canInterface->canBusCfg.rxStatus));
}

/**
 * @brief 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return true 
 * @return false 
 */
bool transmitRequired   (CanIf_t *canInterface)
{
    uint8_t frameIndex = 0;
    uint16_t txReq = 0u;
    for(frameIndex = 0u; frameIndex < canInterface->txIfFrame_no; ++frameIndex)
    {
        /* Check if update time has expired */
        if(true == canInterface)
        if(true == canInterface->txIfFrames[frameIndex].frameUpdated)
        {
            txReq |= 1 << frameIndex;
        }
    }
    return txReq;
}

/**
 * @brief 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return true 
 * @return false 
 */
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


void attemptFrameTransmission(CanIf_t *canInterface, uint8_t frameIndex)
{
    uint8_t TxStatus = 0u;
    
    /* Check if any TX buffer is available and retries are available for frame */
    if(0 < canInterface->txIfFrames[frameIndex].retriesLeft)
    {
        TxStatus = MCP2515_sendMessage(&(canInterface->canBusCfg), &(canInterface->txIfFrames[frameIndex].canFrame));

        if(MCP2515_E_ALLTXBUSY == TxStatus)
        {
            /* Report TX_BUFFERS_BUSY error */
            --(canInterface->txIfFrames[frameIndex].retriesLeft);
        }
        else if(MCP2515_E_FAILTX == TxStatus)
        {
            /* Report TX_FAILED error */
            --(canInterface->txIfFrames[frameIndex].retriesLeft);
        }
#if (CANIF_DEV_ERRORS == 1)
        else if(MCP2515_E_MSGTOOBIG == TxStatus)
        {
            /* Report FRAME_SIZE_INVALID error */
        }
#endif
        else /* Frame was sent successfully */
        {
            /* Reset retry counter */
            canInterface->txIfFrames[frameIndex].retriesLeft = canInterface->txIfFrames[frameIndex].updateRetries;
        }
    }
    else
    {
        /* Report NO_RETRIES_LEFT error */
    }
}


/**
 * @brief 
 * 
 * @param canInterface The CAN Interface configuration structure
 * @return true 
 * @return false 
 */
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
