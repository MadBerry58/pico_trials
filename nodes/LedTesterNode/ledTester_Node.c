#include "../../picoOS/picoOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "ledTesterSM/ledTesterSM.h"
#include "ledTester_config.h"
#include <string.h>

#define NODE_ID 3u //Node IDs wil be given by the user/configuration sw

bool     Frame_SWCdata_Updated;

bool     pushButton_updateFlag;
bool     encoderPosition_updateFlag;

bool     buttonState       = false;
uint32_t buttonTimePressed = 0u;
uint8_t  encoderPosition   = 0u;
uint8_t  white_intensity   = 0u;
uint8_t  white_color       = 0u;

can_frame Rx_messageBuffer = 
{
    .can_id     = 0,
    .can_dlc    = 0,
    .data       = {0,0,0,0,0,0,0,0}
};

can_frame Tx_messageBuffer = 
{
    .can_id     = 174u,
    .can_dlc    = 8,
    .data       = {0,0,0,0,0,0,0,0}
};

int main()
{
    uint32_t nodeError = 0u;
    NodeType_e node_type = LedTester;

    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, NODE_ID);

    /* Reset previous core code */
    multicore_reset_core1();

    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_ledTesterNodeSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        if(
            (true == Frame_SWCdata_Updated) ||
            (true == pushButton_updateFlag)
        )
        {
            ((frame0_dev_tx_type*)&(Tx_messageBuffer.data))->button_time_pressed = buttonTimePressed / (1000 * 100);
            ((frame0_dev_tx_type*)&(Tx_messageBuffer.data))->encoder_position    = encoderPosition  ;
            ((frame0_dev_tx_type*)&(Tx_messageBuffer.data))->button_state        = buttonState      ;
            ((frame0_dev_tx_type*)&(Tx_messageBuffer.data))->white_intensity     = white_intensity  ;
            ((frame0_dev_tx_type*)&(Tx_messageBuffer.data))->white_color         = white_color      ;
            
            network_send_canFrame(&(Tx_messageBuffer));
            Frame_SWCdata_Updated = false;
            pushButton_updateFlag = false;
        }

        if(1 == network_read_canFrame(&(Rx_messageBuffer)))
        {
            if(Rx_messageBuffer.can_id == 174u)
            {
                // memcpy(&(localFrame0DataRx), &(Rx_messageBuffer.data), 8u);
                printf( "RX_button_state       : %d\n", ((frame0_dev_tx_type*)&(Rx_messageBuffer.data))->button_state                );
                printf( "RX_button_time_pressed: %f\n", ((frame0_dev_tx_type*)&(Rx_messageBuffer.data))->button_time_pressed / 10.00 );
                printf( "RX_encoder_position   : %d\n", ((frame0_dev_tx_type*)&(Rx_messageBuffer.data))->encoder_position            );
                printf( "RX_white_intensity    : %d\n", ((frame0_dev_tx_type*)&(Rx_messageBuffer.data))->white_intensity             );
                printf( "RX_white_color        : %d\n", ((frame0_dev_tx_type*)&(Rx_messageBuffer.data))->white_color                 );
            }
            else
            {
                printf("CAN frame ID:  %lu \n", Rx_messageBuffer.can_id);
                printf("CAN frame DLC: %lu \n", Rx_messageBuffer.can_dlc);
                for(int i = 0; i < Rx_messageBuffer.can_dlc; ++i)
                {
                  printf("CAN frame byte %d:  %lu \n", i, Rx_messageBuffer.data[i]);
                }
            }
        }
    }
    printf("End of program: %llu", nodeError);
}