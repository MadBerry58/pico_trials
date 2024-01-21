#include "ledTesterSM.h"
#include "../ledTester_config.h"

void core_ledTesterNodeSM()
{    
    /* initialize components */
    pushButtonSM_init       ();
    init_encoderSM_swc      ();

    controlLogic_ledTesterSM_init ();
    
    coldLedSM_init          ();
    // warmLedSM_init          ();

    /* Main sequence */
    while (1) {
        /* read inputs */
        pushButtonSM_run        ();
        run_encoderSM_swc       ();

        /* input/output logic */
        controlLogic_ledTesterSM_run  ();

        /* update outputs */
        coldLedSM_run           ();
        // warmLedSM_run             ();
        
        ///TODO: replace with scheduler functionality
        sleep_ms                (CYCLE_TIME);
        // gpio_xor_mask(1u << PICO_DEFAULT_LED_PIN);
    }
    
    /* IDEA: inter-component comm: data+update_notification
        -consume notification   - reader resets the update notification flag on reading data
        -cycle reset            - notification flags are reset at the end of the cycle
        -persist                - notification flag is reset by the emmiter when value remains unchanged
    */
}