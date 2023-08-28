#include "RGBws2812SM.h"
#include "RGBws2812_Internal.h"

RGBws2812_SM_State SM_state = rgbSM_UNININIALISED;
bool SM_loop_control = false;
uint32_t updateTimeout = 0u;
Pattern_t internalPattern;
bool pattern_active = false;
uint8_t localError = 0u; ///TODO: add error handling

uint8_t RGBws2812SM_init()
{
    //Bind RGB control pin
}

uint8_t RGBws2812SM_run()
{
    while(SM_loop_control)
    {
        switch (SM_state)
        {
            case rgbSM_UNININIALISED:
                /* On entry */
                localError = init_SM_internals();

                /* On Transition */
                if(E_OK != localError)
                {
                    /* Transition SM into fault state */
                    SM_state = rgbSM_FAULT;
                    SM_loop_control = true;
                }
                else
                {
                    /* Set state and exit SM */
                    SM_state = rgbSM_INITIALISED;
                    SM_loop_control = false;
                }

                /* On exit */

            break;

            case rgbSM_INITIALISED:
                /* On entry */
                localError = pattern_checkExisting();

                /* On Transition */
                if(E_OK != localError)
                {
                    /* Transition SM into fault state */
                    SM_state = rgbSM_FAULT;
                    SM_loop_control = true;
                }
                else
                if(patternPreviouslySet())
                {
                    SM_state = rgbSM_UPDATE_PATTERN;
                    SM_loop_control = true;
                }
                else
                {
                    SM_state = rgbSM_IDLE;
                    SM_loop_control = true;
                }

                /* On exit */

            break;

            case rgbSM_IDLE:
                /* On entry */
                /* update internal timers and request notifications */
                check_for_requests();

                /* On Transition */
                if(request_setPattern() || request_stopPattern())
                {//set/stopPattern check internally for dynamic pattern timers or requests 
                    SM_state = rgbSM_UPDATE_PATTERN;
                    SM_loop_control = true;
                }
                else
                {
                    SM_state = rgbSM_IDLE;
                    SM_loop_control = false;
                }
                /* On exit */
            break;

            case rgbSM_UPDATE_PATTERN:
                /* On entry */

                /* On Transition */
                if(request_stopPattern())
                {
                    pattern_stop();
                    /* Allow SM to go into IDLE state */
                    SM_state = rgbSM_IDLE;
                    pattern_active = false;
                    SM_loop_control = false;
                }
                else
                if(request_setPattern())
                {
                    pattern_set(internalPattern);
                    SM_state = rgbSM_IDLE;
                    pattern_active  = true;
                    SM_loop_control = false;
                }
                else
                {
                    pattern_stop();
                    SM_state        = rgbSM_FAULT;
                    pattern_active  = false;
                    SM_loop_control = false;
                    ///TODO: add error handling
                }
                /* On exit */

            break;

            case rgbSM_STOPPED:
                /* On entry */

                /* On Transition */
                if(startRequest_SM)
                {
                    SM_loop_control = true;
                    SM_state = rgbSM_IDLE;
                }
                else
                if(reinitRequest_SM)
                {
                    SM_loop_control = true;
                    SM_state = rgbSM_UNININIALISED;
                }
                else
                {
                    SM_loop_control = false;
                    SM_state = rgbSM_STOPPED;
                }
                /* On exit */

            break;

            case rgbSM_FAULT:
                /* On entry */

                /* On Transition */

                /* On exit */
                /* Return SM error */
                SM_loop_control = false;
                notifyHost();

            break;
            
            default:
                /* Allow SM to go into FAULT state */
                SM_state = rgbSM_FAULT;
                SM_loop_control = true;
            break;
        }
    }
}