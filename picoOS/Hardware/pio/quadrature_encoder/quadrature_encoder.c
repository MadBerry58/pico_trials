/**
 * Copyright (c) 2021 pmarques-dev @ github
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"
#include "quadrature_encoder.h"
#include "quadrature_encoder.pio.h"

#define ENCODER_STEP_RATE   0 /* 0 - unlimited rate */

//
// ---- quadrature encoder interface example
//
// the PIO program reads phase A/B of a quadrature encoder and increments or
// decrements an internal counter to keep the current absolute step count
// updated. At any point, the main code can query the current count by using
// the quadrature_encoder_*_count functions. The counter is kept in a full
// 32 bit register that just wraps around. Two's complement arithmetic means
// that it can be interpreted as a 32-bit signed or unsigned value, and it will
// work anyway.
//
// As an example, a two wheel robot being controlled at 100Hz, can use two
// state machines to read the two encoders and in the main control loop it can
// simply ask for the current encoder counts to get the absolute step count. It
// can also subtract the values from the last sample to check how many steps
// each wheel as done since the last sample period.
//
// One advantage of this approach is that it requires zero CPU time to keep the
// encoder count updated and because of that it supports very high step rates.
//

/* Helper functions */


/* Exported functions */

/**
 * @brief Initialize SM functionality
 * 
 * @param sm_data State Machine internal data structure
 * @return quadrature_encoder_sm_error 
 */
quadrature_encoder_sm_error init_quadrature_encoder_sm(quadrature_encoder_sm *sm_data)
{
    quadrature_encoder_sm_error retVal;

    /* SM program requires to be first in the PIO memory for logic arithmetic */
    if(pio_can_add_program_at_offset(pio1, &quadrature_encoder_program, 0u))
    {
        pio_add_program_at_offset(pio1, &quadrature_encoder_program, 0u);
        quadrature_encoder_program_init(pio1, sm_data->smID, sm_data->abPin, ENCODER_STEP_RATE);

        gpio_init       (sm_data->buttonPin);
        gpio_set_dir    (sm_data->buttonPin, GPIO_IN);
        gpio_set_inover (sm_data->buttonPin, GPIO_OVERRIDE_INVERT);
        gpio_pull_up    (sm_data->buttonPin);

        sm_data->sm_state = SM_QUADRATURE_READY;
    }
    else
    {
        retVal = SM_QUADRATURE_E_PIO_PROGRAM;
    }


    return retVal;
}

/**
 * @brief Run the quadrature encoder state machine 
 * 
 * @param sm_data State Machine internal data structure
 * @return quadrature_encoder_sm_error 
 */
quadrature_encoder_sm_error run_quadrature_encoder_sm (quadrature_encoder_sm *sm_data)
{
    quadrature_encoder_sm_error retVal = SM_QUADRATURE_E_OK;
    sm_data->loopControl = true;

    while(sm_data->loopControl)
    {
        switch (sm_data->sm_state)
        {
        case SM_QUADRATURE_UNINIT:
            /* SM not initialized. return fault */

            retVal = SM_QUADRATURE_E_UNINITIALIZED;
            sm_data->loopControl = false;

            break;
        
        case SM_QUADRATURE_READY:
            sm_data->loopControl = true;
            sm_data->sm_state = SM_QUADRATURE_RUNNING;
            break;

        case SM_QUADRATURE_RUNNING:
            /* start the state machine */            
            if(SM_QUADRATURE_R_NONE != sm_data->sm_request)
            {
                switch(sm_data->sm_request)
                {
                    case SM_QUADRATURE_R_RESET:
                        sm_data->sm_state = SM_QUADRATURE_UNINIT;
                        break;

                    case SM_QUADRATURE_R_STOP:
                        sm_data->sm_state = SM_QUADRATURE_STOPPED;
                        break;
                    
                    case SM_QUADRATURE_R_START:
                        // sm_data->sm_state = SM_QUADRATURE_RUNNING;
                        retVal = SM_QUADRATURE_E_REQUEST_SEQUENCE;
                        break;
                    
                    default:
                        retVal = SM_QUADRATURE_E_UNKNOWN_REQUEST;
                        break;
                }
                // sm_data->loopControl = true;
                sm_data->sm_request = SM_QUADRATURE_R_NONE;
            }
            else             
            {
                /* Read sm data. Half rotation changes current rotation by 1, thus 2 is used as a debounce */
                *(sm_data->rotationOutput) = (quadrature_encoder_get_count(pio1, sm_data->smID) / 2u);
                *(sm_data->buttonOutput)   = (gpio_get(sm_data->buttonPin));
                
                if(
                    (sm_data->prevRotation != (*(sm_data->rotationOutput))) ||
                    (sm_data->prevButton   != (*(sm_data->buttonOutput  )))
                )
                {
                    sm_data->notificationFlag = SM_QUADRATURE_N_UPDATE;
                }
                else
                {
                    sm_data->notificationFlag = SM_QUADRATURE_N_NONE;
                }

                // sm_data->sm_state         = SM_QUADRATURE_RUNNING;
                sm_data->loopControl = false;
                retVal = SM_QUADRATURE_E_OK;
            }
            break;
        
        case SM_QUADRATURE_STOPPED:
            /* Stop SM */
            if(SM_QUADRATURE_R_NONE != sm_data->sm_request)
            {
                switch(sm_data->sm_request)
                {
                    case SM_QUADRATURE_R_RESET:
                        sm_data->sm_state = SM_QUADRATURE_UNINIT;
                        sm_data->loopControl = false;
                        break;

                    case SM_QUADRATURE_R_STOP:
                        sm_data->notificationFlag = SM_QUADRATURE_N_LOW_PRIO_ERROR;
                        sm_data->sm_state = SM_QUADRATURE_STOPPED;
                        sm_data->loopControl = false;
                        retVal = SM_QUADRATURE_E_REQUEST_SEQUENCE;
                        break;
                    
                    case SM_QUADRATURE_R_START:
                        sm_data->sm_state    = SM_QUADRATURE_RUNNING;
                        sm_data->loopControl = true;
                        break;
                    
                    default:
                        sm_data->sm_state = SM_QUADRATURE_STOPPED;
                        sm_data->loopControl = false;
                        sm_data->notificationFlag = SM_QUADRATURE_N_MEDIUM_PRIO_ERROR;
                        retVal = SM_QUADRATURE_E_UNKNOWN_REQUEST;
                        break;
                }
                /* Clear out host request */
                sm_data->sm_request = SM_QUADRATURE_R_NONE;
            }
            else
            {
                // sm_data->sm_state = SM_QUADRATURE_STOPPED;
                sm_data->loopControl = false;
                retVal = SM_QUADRATURE_E_OK;
            }
            break;

        case SM_QUADRATURE_FAULT:
            /* return error message */
            if(SM_QUADRATURE_R_NONE != sm_data->sm_request)
            {
                switch(sm_data->sm_request)
                    {
                        case SM_QUADRATURE_R_RESET:
                            sm_data->sm_state         = SM_QUADRATURE_UNINIT;
                            sm_data->loopControl      = false;
                            break;

                        case SM_QUADRATURE_R_STOP:
                            sm_data->sm_state         = SM_QUADRATURE_FAULT;
                            sm_data->loopControl      = false;
                            
                            sm_data->notificationFlag = SM_QUADRATURE_N_LOW_PRIO_ERROR;
                            retVal = SM_QUADRATURE_E_REQUEST_SEQUENCE;
                            break;
                        
                        case SM_QUADRATURE_R_START:
                            sm_data->sm_state         = SM_QUADRATURE_RUNNING;
                            sm_data->loopControl      = true;
                            
                            sm_data->notificationFlag = SM_QUADRATURE_N_LOW_PRIO_ERROR;
                            retVal = SM_QUADRATURE_E_STARTED_FROM_FAULT;
                            break;
                        
                        default:
                            sm_data->sm_state    = SM_QUADRATURE_STOPPED;
                            sm_data->loopControl = false;

                            sm_data->notificationFlag = SM_QUADRATURE_N_MEDIUM_PRIO_ERROR;
                            retVal = SM_QUADRATURE_E_UNKNOWN_REQUEST;
                            break;
                    }
            }
            else
            {
                // sm_data->sm_state    = SM_QUADRATURE_FAULT;
                sm_data->loopControl = false;

                sm_data->notificationFlag = SM_QUADRATURE_N_LOW_PRIO_ERROR;
                retVal = SM_QUADRATURE_E_FAULT_NOT_RESOLVED;            
            }
            break;

        default:
            /* Unknown request  */
            sm_data->loopControl      = false;
            sm_data->notificationFlag = SM_QUADRATURE_N_HIGH_PRIO_ERROR;
            sm_data->sm_state         = SM_QUADRATURE_FAULT;
            retVal                    = SM_QUADRATURE_E_UNKNOWN_STATE;
            break;
        }
    }

    return retVal;
}