#include "pico/multicore.h"

#include "LightController_config.h"
#include "lightControllerSM/lightControllerSM.h"

#define LIGHT_CONTROLLER_ID 2U

uint32_t 	nodeError = 0u;
NodeType_e 	node_type = LightController;

uint32_t LightController_RxFrameIDs[] = 
{
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000,
    0b00000000000000000000000000000000
};

/* Buffers storing sent data */

NodeTxFrameData lightControllerTxFrames[] = 
{
    // lightController_TX_statusFrame
    {
        {
            .can_id  = 0b00000000000000000000000000000001u,
            .can_dlc = 8,
            .data    = { 16, 18, 23, 14, 22, 11, 4, 1 }
        },
        1000u,
        1000u
    },

    // lightController_TX_request/response frame
    {
        {
            .can_id  = 0b00000000000000000000000000000011,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        2000u,
        2000u
    },

    // lightController_TX_errorFrame
    {
        {
            .can_id  = 0b00000000000000000000000000000101,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        5000u,
        5000u
    },

    // lightController_RX_updateFrame
    {
        {
            .can_id  = 0b00000000000000000000000000001001,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        8000u,
        8000u
    },

    // lightController_RX_commandFrame
    {
        {
            .can_id  = 0b00000000000000000000000000010001,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        10000u,
        10000u
    },
};

/* Buffers for received frame data */

NodeRxFrameData lightControllerRxFrames[] = 
{
    // lightController_TX_statusFrame
    {
        {
            .can_id  = 0b00000000000000000000000000000001u,
            .can_dlc = 8,
            .data    = { 16, 18, 23, 14, 22, 11, 4, 1 }
        },
        1000u,
        1000u
    },

    // lightController_TX_request/response frame
    {
        {
            .can_id  = 0b00000000000000000000000000000011,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        2000u,
        2000u
    },

    // lightController_TX_errorFrame
    {
        {
            .can_id  = 0b00000000000000000000000000000101,
            .can_dlc = 8,
            .data    = { 0, 0, 0, 0, 0, 0, 0, 0 }
        },
        5000u,
        5000u
    }
};

can_frame Rx_messageBuffer;

int main()
{

    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, LIGHT_CONTROLLER_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_lightControllerSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        // for(uint8_t frameIndex = 0; frameIndex < sizeof(lightControllerTxFrames) / sizeof(lightControllerTxFrames[0]); ++frameIndex)
        // {
        //     if(lightControllerTxFrames[frameIndex].nextUpdate < (time_us_32()/1000u))
        //     {
        //         network_send_canFrame(&(lightControllerTxFrames[frameIndex].frame));
        //         lightControllerTxFrames[frameIndex].nextUpdate += lightControllerTxFrames[frameIndex].updateTimeMS;
        //     }
        // }
        network_read_canFrame(&(Rx_messageBuffer));
    }
    printf("End of program: %llu", nodeError);
}