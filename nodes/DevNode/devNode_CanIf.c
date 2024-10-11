#include "../../../picoOS/picoOS_Types.h"
#include "dev_config.h"

enum {
    FRAME_0x3B6_SIGNAL_START_INDEX = 0,
    FRAME_0x6A2_SIGNAL_START_INDEX = 2,
} Frame_Signal_Index;

CanIf_Signal RxSignals[] = 
{
    { //Test Rx Signal 0 
        .ipcData.uint8Data        = 0u,
        .type                     = IPC_UINT8,

        .bitPosition              = 0u,
        .bitSize                  = 5u,

        .updateCallback           = NULL,

        .dataRangeLow.uint8Data   = 0u,
        .dataRangeHigh.uint8Data  = ((1<<5u) - 1),
        .invalidValueCallback     = NULL,

        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 1
        .ipcData.uint16Data       = 0u,
        .type                     = IPC_UINT16,

        .bitPosition              = 5u,
        .bitSize                  = 14u,

        .updateCallback           = NULL,

        .dataRangeLow.uint16Data  = 0u,
        .dataRangeHigh.uint16Data = ((1<<14u) - 1),
        .invalidValueCallback     = NULL,

        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 2
        .ipcData.uint32Data       = 0u,
        .type                     = IPC_UINT32,

        .bitPosition              = 0u,
        .bitSize                  = 26u,

        .updateCallback           = NULL,

        .dataRangeLow.uint32Data  = 0u,
        .dataRangeHigh.uint32Data = ((1<<26u) - 1),
        .invalidValueCallback     = NULL,

        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 3
        .ipcData.uint64Data       = 0u,
        .type                     = IPC_UINT64,

        .bitPosition              = 26u,
        .bitSize                  = 34u,

        .updateCallback           = NULL,

        .dataRangeLow.uint64Data  = 0u,
        .dataRangeHigh.uint64Data = ((1<<34u) - 1),
        .invalidValueCallback     = NULL,

        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 4
        .ipcData.uint64Data       = 0u,
        .type                     = IPC_SINT8,

        .bitPosition              = 60u,
        .bitSize                  = 4u,

        .updateCallback           = NULL,

        .dataRangeLow.uint64Data  = 0,
        .dataRangeHigh.uint64Data = ((1<<4u) - 1),
        .invalidValueCallback     = NULL,

        .timeoutCallback          = NULL,
    },
};

CanIf_Frame devNode_CanIf_TxFrames[] = 
{
    { // Test Tx frame 0x3b5
        .canFrame = 
        {
            .can_id           = 0x3B5,
            .can_dlc          = 6,
            .data             = {0},
        },

        .frameUpdateCallback  = NULL,

        .signals              = NULL,
        .signalNo             = 0U,
        .frameUpdated         = false,

        .updatePeriod_ms      = 0u,
        .updateRetries        = 0u,
        .retriesLeft          = 0u,
    },
    { // Test Tx frame 0x6a1
        .canFrame = 
        {
            .can_id           = 0x6A1,
            .can_dlc          = 2,
            .data             = {0},
        },

        .frameUpdateCallback  = NULL,

        .signals              = NULL,
        .signalNo             = 0U,
        .frameUpdated         = false,

        .updatePeriod_ms      = 0u,
        .updateRetries        = 0u,
        .retriesLeft          = 0u,
    },
};

CanIf_Frame devNode_CanIf_RxFrames[] = 
{
    { // Test Rx frame 0x3b6
        .canFrame = 
        {
            .can_id           = 0x3B6,
            .can_dlc          = 6,
            .data             = {0},
        },

        .frameUpdateCallback  = NULL,

        .signals              = &(RxSignals[FRAME_0x3B6_SIGNAL_START_INDEX]),
        .signalNo             = 2u,
        .frameUpdated         = false,

        .updatePeriod_ms      = 0u,
        .updateRetries        = 0u,
        .retriesLeft          = 0u,
    },
    { // Test Rx frame 0x6a2
        .canFrame = 
        {
            .can_id           = 0x6A2,
            .can_dlc          = 2,
            .data             = {0},
        },

        .frameUpdateCallback  = NULL,

        .signals              = &(RxSignals[FRAME_0x6A2_SIGNAL_START_INDEX]),
        .signalNo             = 0U,
        .frameUpdated         = false,

        .updatePeriod_ms      = 0u,
        .updateRetries        = 0u,
        .retriesLeft          = 0u,
    },
};

const CanIf_t devNode_CanIf = 
{
    .canBusCfg = 
    {
        .CS_PIN       = MCP2515_SPI_CS,
        .TX_PIN       = MCP2515_SPI_MOSI,
        .RX_PIN       = MCP2515_SPI_MISO,
        .SCK_PIN      = MCP2515_SPI_CLK,
        .INT_PIN      = MCP2515_SPI_INT,
        .SPI_CLOCK    = MPC2515_SPI_FREQ,
        .rxStatus     = 0,
        .icStatus     = 0,
        .error        = 0
    },
    .txIfFrames       = devNode_CanIf_TxFrames,
    .txIfFrame_no     = sizeof(devNode_CanIf_TxFrames) / sizeof(devNode_CanIf_TxFrames[0]),
    .rxIfFrames       = devNode_CanIf_RxFrames,
    .rxIfFrame_no     = sizeof(devNode_CanIf_RxFrames) / sizeof(devNode_CanIf_RxFrames[0])

};