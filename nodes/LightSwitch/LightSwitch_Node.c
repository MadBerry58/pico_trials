#include "../../picoOS/picoOS.h"

#include "pico/multicore.h"
#include "lightSwitchSM/lightSwitchSM.h"
#include "LightSwitch_CanIf.h"

#define LIGHT_SWITCH_ID 2U

int main()
{
    /* Initialize base OS functionality */
    init_OS(LightController, LIGHT_SWITCH_ID);

    /* Reset previous core code */
    multicore_reset_core1();
    /* Initialize node-specific functionality on core 1 */
    // multicore_launch_core1(core_lightSwitchSM);

    // nodeError = multicore_fifo_pop_blocking();
    /* Start the OS and trigger the node scheduler loop */
    // run_OS();

    /* Init */
    init_Comms(&(LightSwitch_CanIf));

    while(1)
    {
        run_Comms(&(LightSwitch_CanIf));

        LightSwitch_CanIf.txIfFrames[1].canFrame.data[0] ++;
        MCP2515_sendMessage     (&(LightSwitch_CanIf.canBusCfg), &(LightSwitch_CanIf.txIfFrames[1].canFrame));
        LightSwitch_CanIf.txIfFrames[LIGHTSWITCH_TX_BROADCAST_FRAME_INDEX].canFrame.can_id = 0x11;
        sleep_ms(3000u);
    }
}