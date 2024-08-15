#include "../../picoOS/picoOS.h"

#include "pico/multicore.h"
#include "lightSwitchSM/lightSwitchSM.h"

#define LIGHT_SWITCH_ID 2U

int main()
{
    /* Initialize base OS functionality */
    init_OS(LightController, LIGHT_SWITCH_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_lightSwitchSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        
        sleep_ms(10u);
    }
}