#include "../../picoOS/picoOS.h"

#include "pico/multicore.h"
#include "lightSwitchSM/lightSwitch_data.h"
#include "lightSwitchSM/lightSwitchSM.h"

#define LIGHT_SWITCH_ID 2U

uint32_t 	nodeError = 0u;
NodeType_e 	node_type = LightController;


int main()
{

    /* Initialize base OS functionality */
    stdio_init_all();
    init_OS(node_type, LIGHT_SWITCH_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    multicore_launch_core1(core_lightSwitchSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();
    while(1)
    {
        if(true == encoderPosition_updateFlag)
        {
            printf("Quadrature position updated to: %d\n", encoderPosition);
            encoderPosition_updateFlag = false;
        }

        if(true == pushButton_updateFlag)
        {
            if(true == buttonState)
            {
                printf("Button pressed\n");
            }
            else
            {
                printf("Button released\n");
            }
            pushButton_updateFlag = false;
        }else if(true == buttonState)
        {
            printf("Button pressed for %d seconds\n", (buttonTimePressed / 1000u));
        }
    sleep_ms(10u);
    }
    printf("End of program: %llu", nodeError);
}