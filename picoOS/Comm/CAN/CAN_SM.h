#ifndef CAN_SM_H
#define CAN_SM_H
#include "CAN_SM_APIs.h"

#include "../../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../../picoOS_Types.h"

void CAN_SM_init    (CanIf_t *canInterface);

void CAN_SM_run     (CanIf_t *canInterface);

#endif