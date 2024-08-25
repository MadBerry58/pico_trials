#ifndef COMM_H
#define COMM_H

#include "../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../picoOS_Types.h"

Errors_OS_e init_Comms(CanIf_t *canInterface);

Errors_OS_e run_Comms (CanIf_t *canInterface);

#endif