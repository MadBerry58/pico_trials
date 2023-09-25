#include "devSM.h"

void internalLogic_devNodeSM();

void core_devNodeSM()
{
    uint8_t error = 0;
    /* initialize components */
    if(SM_QUADRATURE_E_OK   != init_quadrature_encoder_sm(&quadratureSM))
    {
        error = 1;
    }
    else
    if(SM_WS2812_E_OK       != init_ws2812(&ws2812SM))
    {
        error = 1;
        printf("RGB PIO init error %d\n", error);
    }
    else
    {
        /* All components initialized correctly */
        error = 0;
    }
    
    /* Main sequence */
    ///TODO: replace with scheduler functionality
    while (1) {
        /* read inputs */
        run_quadrature_encoder_sm(&quadratureSM);
        
        /* input/output logic */
        internalLogic_devNodeSM();

        /* update outputs */
        run_ws2812(&ws2812SM);
        
        sleep_ms(CYCLE_TIME);
    }
    /* IDEA: inter-component comm: data+update_notification
        -consume notification   - reader resets the update notification flag on reading data
        -cycle reset            - notification flags are reset at the end of the cycle
        -persist                - notification flag is reset by the emmiter when value remains unchanged
    */
}

void internalLogic_devNodeSM()
{
    
}