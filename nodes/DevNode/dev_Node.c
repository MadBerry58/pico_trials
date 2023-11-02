#include "../../picoOS/picoOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "devSM/devSM.h"

#define NODE_ID 1u //Node IDs wil be given by the user/configuration sw

uint8_t messageBuffer = 0u;
uint8_t messageSize   = 0u;

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
        network_read(&(messageBuffer), &(messageSize));
    }
    printf("End of program: %llu", nodeError);
}