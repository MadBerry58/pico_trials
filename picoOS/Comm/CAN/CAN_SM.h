#ifndef CAN_SM_H
#define CAN_SM_H

#include "../../SystemServices/ErrorHandling/ErrorCodes.h"
typedef enum
{
    COMM_SM_S_UNINITIALIZED,
    COMM_SM_S_IDLE,
    COMM_SM_S_READING,
    COMM_SM_S_WRITING,

    COMM_SM_S_FAULT
} CAN_SM_state;

void CAN_SM_init    (void);

void CAN_SM_run     (void);

#endif