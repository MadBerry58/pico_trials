#include "devSM.h"
#include "../dev_config.h"

void core_devNodeSM()
{    
    /* initialize components */
    pushButtonSM_init          ();
    // tempSensSM_init         ();
    controlLogic_devSM_init();
    init_encoderSM_swc();
    // rgb_ringSM_init         ();
    // rgb_stripSM_init        ();
    // warmledSM_init             ();
    // coldledSM_init             ();
    // motorControlSM_init     ();
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, 1);
    
    /* Main sequence */
    while (1) {
        /* read inputs */
        pushButtonSM_run          ();
        run_encoderSM_swc();

        // tempSensSM_run         ();
        
        /* input/output logic */
        controlLogic_devSM_run();

        /* update outputs */
        // rgb_ringSM_run         ();
        // rgb_stripSM_run        ();
        coldLedSM_run             ();
        warmLedSM_run             ();
        // motorControlSM_run     ();
        
        ///TODO: replace with scheduler functionality
        sleep_ms                    (CYCLE_TIME);
        // gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN);
    }
    
    /* IDEA: inter-component comm: data+update_notification
        -consume notification   - reader resets the update notification flag on reading data
        -cycle reset            - notification flags are reset at the end of the cycle
        -persist                - notification flag is reset by the emmiter when value remains unchanged
    */
}