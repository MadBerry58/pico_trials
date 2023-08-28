#include "devSM.h"
#include "configuration.h"

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
    /* compute necessary notification update flags */
    if(buttonState != prevButtonState)
    {
        if(BUTTON_PRESSED == buttonState)
        {
            printf("Button Pressed\n");
            msPressed = 0u;
        }
        else
        {
            printf("Button Released\n");
            ///TODO: add timer functionality
            /* Check if timer is pressed for certain amounts of time */
            if(msPressed > SWITCH_TIME)
            {/* Switch light control */
                printf("Switching target\n");
                target = (target + 1) % no_of_Targets;
                msPressed = 0u;
            }
            else
            if(msPressed > CUSTOMIZE_TIME)
            {/* Customize pattern */
                printf("Switching to customization\n");
                msPressed = 0u;
            }
            else
            {/* Change pattern */

            }
        }
    }
    else
    if(BUTTON_PRESSED == buttonState)
    {
        ///TODO: add timer functionality
        msPressed += CYCLE_TIME;
        if(0u > (CYCLE_TIME % prevTime))
        {
            prevTime += 1000;
            printf("Button pressed for %d seconds\n", (msPressed / 1000u));
        }
    }
    else
    {
        /* Button is not pressed */
    }        

    if(encoderPosition_old != encoderPosition)
    {
        // if(
        //     (RGB_control == target)
        //     //  && ()
        // )
        // {
        //     case :
        //         /* notify rgb SM for update */
        //         ws2812SM.patternLocation = (&(patterns[encoderPosition % patternNumber]));
        //         ws2812SM.updateFlag = true;
        //         break;
        //     case LED_control:
        //         /* notify white LED SM for update */
        //         break;
        //     default:

        //         break;
        // }
    }
    else
    {
        /* no pattern update */
    }
}