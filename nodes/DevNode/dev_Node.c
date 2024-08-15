#include "../../picoOS/picoOS.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "devSM/devSM.h"
#include "dev_config.h"
#include <string.h>

#include "../../../picoOS_Types.h"

extern const CanIf_t devNode_CanIf;

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

    }
}