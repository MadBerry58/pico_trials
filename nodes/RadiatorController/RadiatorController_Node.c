#include "../../picoOS/picoOS.h"

#include "pico/multicore.h"
#include "radiatorControllerSM/radiatorControllerSM.h"

#define RADIATOR_CONTROL_ID 3U

uint32_t 	nodeError = 0u;
NodeType_e 	node_type = RadiatorController;

int main()
{

    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, RADIATOR_CONTROL_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_radiatorControllerSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {

    }
    printf("End of program: %llu", nodeError);
}