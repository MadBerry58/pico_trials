#ifndef LIGHTSWITCH_CANIF_H
#define LIGHTSWITCH_CANIF_H

#include "../../picoOS/picoOS_Types.h"

#define MHZ             1000000
#define SPI_FREQ_MHZ    16u * MHZ
#define SPI_RX          12u//16 12
#define SPI_CS          13u//17 13
#define SPI_CLK         14u//18 14
#define SPI_TX          15u//19 15
#define MCP_INT         20u
#define TEST_SIZE       1u

#define BROADCAST_FRAME_ID 0x029u

#define LIGHTCONTROLLER_NODE_TYPE_ID 0x04u

enum LightController_Tx_Indexes
{
    LIGHTCONTROLLER_TX_BROADCAST_FRAME_INDEX,
    LIGHTCONTROLLER_TX_KEEPALIVE_FRAME_INDEX
};

enum LightController_Rx_Indexes
{
    LIGHTCONTROLLER_RX_NETWORK_CONFIRMATION_FRAME_INDEX,
    LIGHTCONTROLLER_RX_CONTROL_FRAME_INDEX
};

extern CanIf_t LightController_CanIf;

#endif