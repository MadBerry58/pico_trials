#include "picoOS_Types.h"

#define Frame_3B5_SIGNAL_INDEX
#define Frame_3B5_SIGNAL_NO

CanIf_Signal TxFrame_3B6_RxSignals[] = 
{
    { //Test Rx Signal 0 
        .ipcData.uint8Data        = 0u,
        .type                     = IPC_UINT8,

        .bitPosition              = 0u,
        .bitSize                  = 5u,

        .updateCallback           = NULL,

        .dataRangeLow.uint8Data   = 0u,
        .dataRangeHigh.uint8Data  = UINT8_MAX,
        .invalidValueCallback     = NULL,

        .updateTime               = 0u,
        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 1
        .ipcData.uint16Data       = 0u,
        .type                     = IPC_UINT16,

        .bitPosition              = 5u,
        .bitSize                  = 14u,

        .updateCallback           = NULL,

        .dataRangeLow.uint16Data  = 0u,
        .dataRangeHigh.uint16Data = UINT16_MAX,
        .invalidValueCallback     = NULL,

        .updateTime               = 0u,
        .timeoutCallback          = NULL,
    }
};

CanIf_Frame CanIf_Frame_3B5 = 
{
  .canFrame = 
  {
    .can_id   = 0x3B5,
    .can_dlc  = 6,
    .data     = {0},
  },

  .frameUpdateCallback  = NULL,

  .signals          = NULL,
  .signalNo         = 0U,
  .frameUpdated     = false,

  .updatePeriod     = 0u,
  .updateRetries    = 0u,
  .retriesLeft      = 0u,
};

CanIf_Signal Frame_6A2_Signals[] =
{
    {
        .ipcData.uint32Data       = 0u,
        .type                     = IPC_UINT32,

        .bitPosition              = 0u,
        .bitSize                  = 26u,

        .updateCallback           = NULL,

        .dataRangeLow.uint32Data  = 0u,
        .dataRangeHigh.uint32Data = UINT32_MAX,
        .invalidValueCallback     = NULL,

        .updateTime               = 0u,
        .timeoutCallback          = NULL,
    },
    { //Test Rx Signal 3
        .ipcData.uint64Data       = 0u,
        .type                     = IPC_UINT64,

        .bitPosition              = 26u,
        .bitSize                  = 34u,

        .updateCallback           = NULL,

        .dataRangeLow.uint64Data  = 0u,
        .dataRangeHigh.uint64Data = UINT64_MAX,
        .invalidValueCallback     = NULL,

        .updateTime               = 0u,
        .timeoutCallback          = NULL,
    },
};



const CanIf_Frame CanIf_Frame_6A1 = 
{
    .canFrame = 
    {
      .can_id   = 0x6A1,
      .can_dlc  = 2,
      .data     = {0},
    },

    .frameUpdateCallback  = NULL,

    .signals    = NULL,
    .signalNo    = 0U,
    .frameUpdated     = false,

    .updatePeriod     = 0u,
    .updateRetries    = 0u,
    .retriesLeft      = 0u,
};

const CanIf_Frame CanIf_Frame_3B6 = 
{ // Test Rx frame 0x3b6
    .canFrame = 
    {
      .can_id   = 0x3B6,
      .can_dlc  = 6,
      .data     = {0},
    },

    .frameUpdateCallback  = NULL,

    .signals          = NULL,
    .signalNo         = sizeof(TxFrame_3B6_RxSignals)/sizeof(TxFrame_3B6_RxSignals[0]),
    .frameUpdated     = false,

    .updatePeriod     = 0u,
    .updateRetries    = 0u,
    .retriesLeft      = 0u,
};

CanIf_Frame CanIf_Frame_6A2 = 
  {
    .canFrame = 
    {
      .can_id   = 0x6A2,
      .can_dlc  = 2,
      .data     = {0},
    },

    .frameUpdateCallback  = NULL,

    .signals          = Frame_6A2_Signals,
    .signalNo         = 0U,
    .frameUpdated     = false,

    .updatePeriod     = 0u,
    .updateRetries    = 0u,
    .retriesLeft      = 0u,
  };