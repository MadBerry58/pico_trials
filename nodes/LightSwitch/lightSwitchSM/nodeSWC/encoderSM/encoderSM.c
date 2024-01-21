#include "encoderSM.h"
#include "../../../LightSwitch_config.h"

/**
 * Copyright (c) 2021 pmarques-dev @ github
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"

/* Import node configuration */
#include "../../../LightSwitch_config.h"

/* Use quadrature encoder template */
#include "../../../picoOS/Templates/QuadratureEncoderSM/QuadratureEncoderSM.h"

uint8_t  encoderPosition;
bool     encoderPosition_updateFlag;

/**
 * @brief 
 * 
 */
quadrature_encoder_sm_pio quadratureSM = {
    .smID             = 0,
    .abPin            = ENCODER_AB_PINS,
    .stepRate         = ENCODER_STEP_RATE,

    .rotationOutput   = &encoderPosition,
    
    .loopControl      = false,
    .prevRotation     = 0,
    
    .notificationFlag = SM_QUADRATURE_N_NONE,
    .sm_state         = SM_QUADRATURE_UNINIT,
    .sm_request       = SM_QUADRATURE_R_NONE
};


uint8_t init_encoderSM_swc()
{
    uint8_t retVal = 0;
    retVal = init_QuadratureEncoderSM_pio(&(quadratureSM));
    
    ///TOPO: process SM init error
    return retVal;
}

uint8_t run_encoderSM_swc()
{
    uint8_t retVal = 0;
    retVal = run_QuadratureEncoderSM_pio(&(quadratureSM));

    if(quadratureSM.notificationFlag != SM_QUADRATURE_N_NONE)
    {
        switch(quadratureSM.notificationFlag)
        {
            case SM_QUADRATURE_N_UPDATE:
                encoderPosition_updateFlag = true;
                break;

            ///TODO: internal fault handling
            case SM_QUADRATURE_N_LOW_PRIO_ERROR:
                break;
            case SM_QUADRATURE_N_MEDIUM_PRIO_ERROR:
                break;
            case SM_QUADRATURE_N_HIGH_PRIO_ERROR:
                break;
            default:
                break;
        }
    printf("Quadrature position updated to: %d\n", encoderPosition);
    }


    ///TOPO: process SM init error
    return retVal;
}