#ifndef PICO_OS_TYPES_H
#define PICO_OS_TYPES_H

/**********************************************************/
/*********************** IPC TypeDefs *********************/
/**********************************************************/

#include "stdint.h"
#include "stdbool.h"

typedef enum
{
    IPC_BOOL  ,
    IPC_UINT8 ,
    IPC_SINT8 ,
    IPC_UINT16,
    IPC_UINT32,
    IPC_UINT64,
} VarType;

typedef union 
{
    bool        booleanData;
    uint8_t     uint8Data ;
    int8_t      sint8Data ;
    uint16_t    uint16Data;
    int16_t     sint16Data;
    uint32_t    uint32Data;
    int32_t     sint32Data;
    uint64_t    uint64Data;
    int64_t     sint64Data;
    float       floatData ;
    double      doubleData;
} IpcContainer;

typedef struct
{
    IpcContainer      ipcData;              // IPC variable containing the signal data
    
    VarType     type;                 // IPC variable type

    uint8_t     bitPosition;          // starting position of the signal inside the CAN frame
    uint8_t     bitSize;              // the length in bits of the signal data object
    uint16_t    offset;
    float       factor;

    void      (*updateCallback)();    // the function called when the signal data update is handled

    IpcContainer      dataRangeLow;         // the lower limit of the valid data range
    IpcContainer      dataRangeHigh;        // the upper limit of the valid data range
    void      (*invalidValueCallback)();

    void      (*timeoutCallback)();   // the function called when the signal data does not update in the required time

    uint8_t     ownerFrameIndex;       // the index of the frame in the frame list
    uint32_t    ownerFrameID;          // the can ID of the frame containing the signal
} CanIf_Signal;

/**********************************************************/
/*********************** CAN TypeDefs *********************/
/**********************************************************/

#include "Hardware/peripherals/spi_drivers/MCP2515_can/canDefinitions.h"
#include "Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"

/**
 * @struct CanIf_Rxframe
 * @brief Structure describing the CAN frame
 * 
 */
typedef struct {
    can_frame       canFrame; /**< the raw CAN frame container */

    void           (*frameUpdateCallback)(void);

    CanIf_Signal   *signals;
    uint8_t         signalNo;
    bool            frameUpdated;
    bool            transmitRequired;

    uint16_t        updatePeriod_ms;
    uint8_t         updateRetries;
    uint8_t         retriesLeft;
} CanIf_Frame;


/**
 * @brief Structure contains the configuration of the MCP2515 configuration
 *        and the associated Rx/Tx frame descriptions
 * @param canBusCfg     The configuration for the used MCP2515 controller
 * @param txIfFrames    Array containing the configuration and data buffers for the accepted CAN frames
 * @param txIfFrame_no  Number of contained Rx CanIf frames
 * @param rxIfFrames    Array containing the configuration and data buffers for the transmitted CAN frames
 * @param rxIfFrame_no  Number of contained Tx CanIf frames
 *  
 * @details As multiple CAN boards can be used at once, multiple CanIf instances may be used
 */

typedef struct
{
    MCP2515_instance    canBusCfg;

    CanIf_Frame        *txIfFrames;
    uint8_t             txIfFrame_no;

    CanIf_Frame        *rxIfFrames;
    uint8_t             rxIfFrame_no;
} CanIf_t;


#endif