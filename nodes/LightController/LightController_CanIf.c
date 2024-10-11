#include "LightController_CanIf.h"

#define BROADCAST_FRAME_SIGNAL_NODE_TYPE_POSITION 0u
#define BROADCAST_FRAME_SIGNAL_NODE_TYPE_SIZE     5u

#define BROADCAST_FRAME_SIGNAL_NODE_ID_POSITION   5u
#define BROADCAST_FRAME_SIGNAL_NODE_ID_SIZE       11u


CanIf_Signal LightController_CanIf_BroadcastFrame_Signals[] = 
{
  {
    .ipcData                  = 0u,
    .type                     = IPC_UINT8,
    .bitPosition              = BROADCAST_FRAME_SIGNAL_NODE_TYPE_POSITION,
    .bitSize                  = BROADCAST_FRAME_SIGNAL_NODE_TYPE_SIZE,
    .dataRangeHigh.uint8Data  = ((1 << BROADCAST_FRAME_SIGNAL_NODE_TYPE_SIZE) - 1u),
    .dataRangeLow.uint8Data   = 0u,
    .updateCallback           = NULL,
    .invalidValueCallback     = NULL,
    .timeoutCallback          = NULL,
    .ownerFrameIndex          = LIGHTCONTROLLER_TX_BROADCAST_FRAME_INDEX,
    .ownerFrameID             = BROADCAST_FRAME_ID
  },

  {
    .ipcData                  = 0u,
    .type                     = IPC_UINT16,
    .bitPosition              = BROADCAST_FRAME_SIGNAL_NODE_ID_POSITION,
    .bitSize                  = BROADCAST_FRAME_SIGNAL_NODE_ID_SIZE,
    .dataRangeHigh.uint16Data = ((1<<BROADCAST_FRAME_SIGNAL_NODE_ID_SIZE) - 1u),
    .dataRangeLow.uint16Data  = 0u,
    .updateCallback           = NULL,
    .invalidValueCallback     = NULL,
    .timeoutCallback          = NULL,
    .ownerFrameIndex          = LIGHTCONTROLLER_TX_BROADCAST_FRAME_INDEX,
    .ownerFrameID             = BROADCAST_FRAME_ID
  },
};
const uint8_t LightController_CanIf_BroadcastFrame_Signal_no = (sizeof(LightController_CanIf_BroadcastFrame_Signals) / sizeof(LightController_CanIf_BroadcastFrame_Signals[0]));

CanIf_Signal LightController_CanIf_KeepAliveFrame_Signals[] = 
{
  {
    .ipcData                  = 0u,
    .type                     = IPC_UINT8,
    .bitPosition              = KEEPALIVE_FRAME_SIGNAL_NODE_TYPE_POSITION,
    .bitSize                  = KEEPALIVE_FRAME_SIGNAL_NODE_TYPE_SIZE,
    .dataRangeHigh.uint8Data  = ((1 << KEEPALIVE_FRAME_SIGNAL_NODE_TYPE_SIZE) - 1u),
    .dataRangeLow.uint8Data   = 0u,
    .updateCallback           = NULL,
    .invalidValueCallback     = NULL,
    .timeoutCallback          = NULL,
    .ownerFrameIndex          = LIGHTCONTROLLER_TX_KEEPALIVE_FRAME_INDEX,
    .ownerFrameID             = LIGHTCONTROLLER_KEEPALIVE_FRAME_ID
  },

  {
    .ipcData                  = 0u,
    .type                     = IPC_UINT16,
    .bitPosition              = KEEPALIVE_FRAME_SIGNAL_NODE_ID_POSITION,
    .bitSize                  = KEEPALIVE_FRAME_SIGNAL_NODE_ID_SIZE,
    .dataRangeHigh.uint16Data = ((1<<BROADCAST_FRAME_SIGNAL_NODE_ID_SIZE) - 1u),
    .dataRangeLow.uint16Data  = 0u,
    .updateCallback           = NULL,
    .invalidValueCallback     = NULL,
    .timeoutCallback          = NULL,
    .ownerFrameIndex          = LIGHTCONTROLLER_TX_BROADCAST_FRAME_INDEX,
    .ownerFrameID             = KEEPALIVE_FRAME_ID
  },
};
const uint8_t LightController_CanIf_BroadcastFrame_Signal_no = (sizeof(LightController_CanIf_BroadcastFrame_Signals) / sizeof(LightController_CanIf_BroadcastFrame_Signals[0]));

CanIf_Frame LightController_CanIf_TxFrames[] = {
  { /* Broadcast frame - ALWAYS FRAME 0 - used in init hardware*/
    .canFrame = 
    {
      .can_id = BROADCAST_FRAME_ID,
      .can_dlc = 8,
      .data[0] = LIGHTCONTROLLER_NODE_TYPE_ID
    },
    .frameUpdateCallback  = NULL,
    .signals              = LightController_CanIf_BroadcastFrame_Signals,
    .signalNo             = LightController_CanIf_BroadcastFrame_Signal_no,
    .frameUpdated         = false,
    .updatePeriod_ms      = 0u,
    .updateRetries        = 0u,
    .retriesLeft          = 1u
  },

  { /* Keep Alive frame */
    .canFrame = 
    {
      .can_id = 0x6B1,
      .can_dlc = 8,
      .data = {0}
    },
    .frameUpdateCallback = NULL,
    .signals = NULL,
    .signalNo = 0u,
    .frameUpdated = false,
    .updatePeriod_ms = 1000u,
    .updateRetries = 10u,
    .retriesLeft = 5
  }
};


CanIf_Frame LightController_CanIf_RxFrames[] = {
  { /* Network confirmation frame */
    .canFrame = 
    {
      .can_id = 0x010,
      .can_dlc = 8,
      .data = {0}
    },
    .frameUpdateCallback = NULL,
    .signals = NULL,
    .signalNo = 0u,
    .frameUpdated = false,
    .updatePeriod_ms = 1000u,
    .updateRetries = 10u,
    .retriesLeft = 5
  },

  { /* LightSwitch control frame */
    .canFrame = 
    {
      .can_id = 0x010,
      .can_dlc = 8,
      .data = {0}
    },
    .frameUpdateCallback = NULL,
    .signals = NULL,
    .signalNo = 0u,
    .frameUpdated = false,
    .updatePeriod_ms = 1000u,
    .updateRetries = 10u,
    .retriesLeft = 5
  },
};


CanIf_t LightController_CanIf = 
{
    .canBusCfg = 
    {
      .CS_PIN         = SPI_CS,
      .TX_PIN         = SPI_TX,
      .RX_PIN         = SPI_RX,
      .SCK_PIN        = SPI_CLK,
      .INT_PIN        = MCP_INT,
      .SPI_CLOCK      = SPI_FREQ_MHZ,
      .SPI_INSTANCE   = spi1
    },

    .txIfFrames = &(LightController_CanIf_TxFrames[0]),
    .txIfFrame_no = sizeof(LightController_CanIf_TxFrames) / sizeof(LightController_CanIf_TxFrames[0]),

    .rxIfFrames = &(LightController_CanIf_RxFrames[0]),
    .rxIfFrame_no = sizeof(LightController_CanIf_RxFrames) / sizeof(LightController_CanIf_TxFrames[0])
};