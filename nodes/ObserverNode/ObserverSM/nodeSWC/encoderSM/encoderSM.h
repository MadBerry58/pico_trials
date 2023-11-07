#ifndef QUADRATURE_ENCODER_H
#define QUADRATURE_ENCODER_H

#include <stdio.h>
#include "pico/stdlib.h"

typedef enum
{
    SM_QUADRATURE_UNINIT,
    SM_QUADRATURE_READY,
    SM_QUADRATURE_RUNNING,
    SM_QUADRATURE_STOPPED,
    SM_QUADRATURE_FAULT
}quadrature_encoder_sm_state;

typedef enum
{
    SM_QUADRATURE_E_OK,
    SM_QUADRATURE_E_PIO_PROGRAM,
    SM_QUADRATURE_E_UNINITIALIZED,
    SM_QUADRATURE_E_UNKNOWN_STATE,
    SM_QUADRATURE_E_UNKNOWN_REQUEST,
    SM_QUADRATURE_E_REQUEST_SEQUENCE,
    SM_QUADRATURE_E_STARTED_FROM_FAULT,
    SM_QUADRATURE_E_FAULT_NOT_RESOLVED,

    SM_QUADRATURE_E_NOK
}quadrature_encoder_sm_error;

typedef enum
{
    SM_QUADRATURE_N_NONE,
    SM_QUADRATURE_N_UPDATE,

    /* Errors are arranged in increasing order */
    SM_QUADRATURE_N_LOW_PRIO_ERROR,
    SM_QUADRATURE_N_MEDIUM_PRIO_ERROR,
    SM_QUADRATURE_N_HIGH_PRIO_ERROR
}quadrature_encoder_sm_notificationType;

typedef enum
{
    SM_QUADRATURE_R_NONE,
    SM_QUADRATURE_R_START,
    SM_QUADRATURE_R_STOP,
    SM_QUADRATURE_R_RESET
}quadrature_encoder_sm_request;

typedef struct 
{
    uint8_t     smID;
    uint8_t     abPin;
    uint8_t     buttonPin;

    bool*       buttonOutput;
    uint8_t*    rotationOutput;

    bool        loopControl;
    bool        prevButton;
    uint8_t     prevRotation;

    quadrature_encoder_sm_notificationType  notificationFlag;
    quadrature_encoder_sm_state             sm_state;
    quadrature_encoder_sm_request           sm_request;
}quadrature_encoder_sm;

quadrature_encoder_sm_error init_quadrature_encoder_sm(quadrature_encoder_sm *sm_data);
quadrature_encoder_sm_error run_quadrature_encoder_sm (quadrature_encoder_sm *sm_data);

#endif