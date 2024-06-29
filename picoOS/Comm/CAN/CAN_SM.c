#include "pico/stdlib.h"
#include "CAN_SM.h"
#include "CAN_SM_APIs.h"

CAN_SM_state state_curr = COMM_SM_S_UNINITIALIZED;
CAN_SM_state state_prev = COMM_SM_S_UNINITIALIZED;

uint8_t SM_request  = 0;

void CAN_SM_init(void)
{
    /* Init Entry */
    init_CAN_Hardware();

    state_curr = COMM_SM_S_IDLE;

    ///TODO: read hw state
    /* 
    if(hardware_init_failed)
    {
        state_curr = COMM_SM_S_FAULT
        state_prev = COMM_SM_S_UNINITIALIZED;
    }
     */
}

void CAN_SM_run(void)
{
    bool loop = true;

    while(loop)
    {
        switch(state_curr)
        {
            case COMM_SM_S_UNINITIALIZED:
            {
                /* On Entry */
                
                /* Do */
                
                /* Transition */
                state_curr = COMM_SM_S_FAULT;
                state_prev = COMM_SM_S_UNINITIALIZED;

                /* On Exit */
                ///TODO: register error
                
                /* Loop control */
                loop = true;

            }
            break;

            case COMM_SM_S_IDLE:
            {
                /* On Entry */
                
                /* Do */
                update_HW_data();

                /* Transition */
                /* 
                if(update_hw_data_failed)
                {
                    state_curr = COMM_SM_S_FAULT;
                    state_prev = COMM_SM_S_IDLE;
                }else
                 */
                if(true == framesReceived())
                {
                    state_curr = COMM_SM_S_READING;
                    state_prev = COMM_SM_S_IDLE;

                    loop = true;
                    
                }
                else
                if(true == transmitRequired())
                {
                    state_curr = COMM_SM_S_WRITING;
                    state_prev = COMM_SM_S_IDLE;

                    loop = true;

                }
                else
                {
                    state_prev = COMM_SM_S_IDLE;
                    loop = false;
                }

                /* On Exit */
                
            }
            break;

            case COMM_SM_S_READING:
            {
                /* On Entry */
                ///TODO: disable CPU0 ISRs
                // irq_set_mask_enabled
                receiveFrames();
                
                /* Do */

                /* Transition */

                /* On Exit */
                ///TODO: enable CPU0 ISRs
            }
            break;

            case COMM_SM_S_WRITING:
            {
                /* On Entry */
                ///TODO: disable CPU0 ISRs
                
                /* Do */

                /* Transition */

                /* On Exit */
                ///TODO: enable CPU0 ISRs

            }
            break;

            case COMM_SM_S_FAULT:
            {
                /* On Entry */
                
                /* Do */

                /* Transition */

                /* On Exit */

            }
            break;

            default:
            {

            }
        }
    }
}

void CAN_SM_transmit_instant(void)
{

}