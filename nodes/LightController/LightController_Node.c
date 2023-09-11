
#include "core_lightController/lightController.h"

void main()
{
    uint32_t nodeError = 0u;
    NodeType_e node_type = Development;
    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, NODE_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_lightSwitch);

    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {

    }
    printf("End of program: %llu", nodeError);
}