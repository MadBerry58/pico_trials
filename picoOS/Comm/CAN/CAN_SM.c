#include "pico/stdlib.h"
#include "CAN_SM.h"
#include "CAN_SM_APIs.h"

typedef enum
{
    COMM_SM_S_UNINITIALIZED,
    COMM_SM_S_IDLE,
    COMM_SM_S_READING,
    COMM_SM_S_WRITING,

    COMM_SM_S_FAULT
} CAN_SM_state;

CAN_SM_state state_curr = COMM_SM_S_UNINITIALIZED;
CAN_SM_state state_prev = COMM_SM_S_UNINITIALIZED;

uint8_t SM_request  = 0;

void CAN_SM_init(CanIf_t *canInterface)
{
    /* Init Entry */
    init_CAN_Hardware(canInterface);

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

void CAN_SM_run(CanIf_t *canInterface)
{
    bool loop = true;

    while(loop)
    {
        switch(state_curr)
        {
            case COMM_SM_S_UNINITIALIZED:
            {
                /* On Entry */
                // No action

                /* Do */
                // No action
                
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
                update_HW_data(canInterface);

                if(true == framesReceived(canInterface))
                {
                    state_curr = COMM_SM_S_READING;
                    state_prev = COMM_SM_S_IDLE;

                    loop = true;
                }
                else
                if(true == transmitRequired(canInterface))
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
                
                /* Do */
                receiveFrames(canInterface);

                /* Transition */
                if(true == framesReceived(canInterface))
                {
                    state_curr = COMM_SM_S_READING;
                    state_prev = COMM_SM_S_READING;

                    loop = true;
                }
                else
                {
                    state_curr = COMM_SM_S_IDLE;
                    state_prev = COMM_SM_S_READING;

                    loop = true;
                }

                /* On Exit */
                ///TODO: enable CPU0 ISRs
            }
            break;

            case COMM_SM_S_WRITING:
            {
                /* On Entry */
                ///TODO: disable CPU0 ISRs
                
                /* Do */
                transmitFrames(canInterface);

                /* Transition */
                if(true == transmitRequired(canInterface))
                {
                    state_curr = COMM_SM_S_WRITING;
                    state_prev = COMM_SM_S_WRITING;

                    loop = true;

                }
                else
                {
                    state_prev = COMM_SM_S_IDLE;
                    loop = false;
                }

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