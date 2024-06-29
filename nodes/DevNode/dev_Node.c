#include "../../picoOS/picoOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "devSM/devSM.h"
#include "dev_config.h"
#include <string.h>

#include "../../picoOS/Comm/IPC/ipc.h"

#define NODE_ID 1u //Node IDs wil be given by the user/configuration sw
extern MCP2515_instance mainBus;

int main()
{
    NodeType_e node_type = Development;
    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, NODE_ID);

    /* Reset previous core code */
    // multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    // multicore_launch_core1(core_devNodeSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        uint8_t     RxStatus = 0u;
        can_frame   frameBuffer;
        
        /* Check if any messages are inside the can buffer */
        MCP2515_getRxStatus(&(mainBus), &(RxStatus));

        if(0 < (RX_RXANY & RxStatus))
        {
           MCP2515_readMessage(&(mainBus), &(frameBuffer));
           printf("Received message:%d", frameBuffer.data);
        }
    }
}