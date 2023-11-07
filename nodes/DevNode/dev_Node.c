#include "../../picoOS/picoOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "devSM/devSM.h"

#define NODE_ID 1u //Node IDs wil be given by the user/configuration sw

bool     Frame_SWCdata_Updated;
extern uint8_t  encoderPosition;

can_frame Rx_messageBuffer;

can_frame Tx_messageBuffer = 
{
    .can_id     = 189u,
    .can_dlc    = 8,
    .data       = {0,0,0,0,0,0,0,0}
};

///TODO: add signal ID frame mapping
void transferData(uint8_t signalID, uint8_t data)
{
    Tx_messageBuffer.can_dlc = 1u;
    Tx_messageBuffer.data[0u] = data;
}

int main()
{
    uint32_t nodeError = 0u;
    NodeType_e node_type = Development;
    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, NODE_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_devNodeSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        if(true == Frame_SWCdata_Updated)
        {
            transferData(0, encoderPosition);
            network_send_canFrame(&(Tx_messageBuffer));
            Frame_SWCdata_Updated = false;
        }
        network_read_canFrame(&(Rx_messageBuffer));
    }
    printf("End of program: %llu", nodeError);
}