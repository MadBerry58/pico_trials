#include "LightSwitch_CanIf.h"

CanIf_Frame LightSwitch_CanIf_TxFrames[] = {
  { /* Broadcast frame - ALWAYS FRAME 0 - used in init hardware*/
    .canFrame = 
    {
      .can_id = BROADCAST_FRAME_ID,
      .can_dlc = 8,
      .data[0] = LIGHTSWITCH_NODE_TYPE_ID
    },

    .frameUpdateCallback = NULL,

    .signals = NULL,
    .signalNo = 0u,
    .frameUpdated = false,

    .updatePeriod_ms = 0,
    .updateRetries = 0u,
    .retriesLeft = 1
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

CanIf_Frame LightSwitch_CanIf_RxFrames[] = {
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
  }
};

CanIf_t LightSwitch_CanIf = 
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

    .txIfFrames = &(LightSwitch_CanIf_TxFrames[0]),
    .txIfFrame_no = sizeof(LightSwitch_CanIf_TxFrames) / sizeof(LightSwitch_CanIf_TxFrames[0]),

    .rxIfFrames = &(LightSwitch_CanIf_RxFrames[0]),
    .rxIfFrame_no = sizeof(LightSwitch_CanIf_RxFrames) / sizeof(LightSwitch_CanIf_TxFrames[0])
};