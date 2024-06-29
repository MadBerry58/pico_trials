#include "QuadratureEncoderSM.h"
#include "../../Hardware/pio/quadrature_encoder/quadrature_encoder.pio.h"

#define GPIO_DIR_INPUT  false
#define GPIO_DIR_OUTPUT true
#define AB_PINS_MASK    0b011
#define C_PIN_MASK      0b100


uint8_t init_QuadratureEncoderSM(QuadratureEncoderSM *encoderSM)
{
    uint8_t retVal = 0u;
    /* Initialize encoder GPIO pins */
    gpio_init(encoderSM->pinNoA);
    gpio_init(encoderSM->pinNoB);
    gpio_init(encoderSM->pinNoC);

    gpio_set_dir(encoderSM->pinNoA, GPIO_DIR_INPUT);
    gpio_set_dir(encoderSM->pinNoB, GPIO_DIR_INPUT);
    gpio_set_dir(encoderSM->pinNoC, GPIO_DIR_INPUT);

    gpio_set_input_hysteresis_enabled(encoderSM->pinNoA, true);
    gpio_set_input_hysteresis_enabled(encoderSM->pinNoB, true);
    gpio_set_input_hysteresis_enabled(encoderSM->pinNoC, true);

    return retVal;
}

uint8_t run_QuadratureEncoderSM(QuadratureEncoderSM *encoderSM)
{
    // uint8_t retVal;
    // uint8_t abVal;
    // bool pinValA;
    // bool pinValB;
    // bool pinValC;

    // pinValA = gpio_get(encoderSM->pinNoA);
    // pinValB = gpio_get(encoderSM->pinNoB);
    // pinValC = gpio_get(encoderSM->pinNoC);
    // abVal = (pinValA << 0) | (pinValB << 1);

    // if((encoderSM->oldState & AB_PINS_MASK) != abVal)
    // {
    //     encoderSM->newState |= abVal;
    // }
    
    // return retVal;
    return 0;
}


uint8_t init_QuadratureEncoderSM_pio(quadrature_encoder_sm_pio *sm_data)
{
    quadrature_encoder_sm_error retVal;

    /* SM program requires to be first in the PIO memory for logic arithmetic */
    if(pio_can_add_program_at_offset(pio1, &quadrature_encoder_program, 0u))
    {
        pio_add_program_at_offset(pio1, &quadrature_encoder_program, 0u);
        quadrature_encoder_program_init(pio1, sm_data->smID, sm_data->abPin, sm_data->stepRate);

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
uint8_t run_QuadratureEncoderSM_pio(quadrature_encoder_sm_pio *sm_data)
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
                
                if(sm_data->prevRotation != (*(sm_data->rotationOutput)))
                {
                    sm_data->prevRotation = (*(sm_data->rotationOutput));
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