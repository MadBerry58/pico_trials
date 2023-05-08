#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#define ERROR_BUFFER_SIZE 16u

#include "ErrorCodes.h"
#include <stdio.h>

typedef struct {
    uint8_t          error_code;
    Error_Source_e   source;
    Error_Priority_e priority;
    Error_Response_e response;
} Error_t;


/**
 * @brief Retrieve next highest priority from error buffer
 * 
 * @return uint8_t 
 */
uint8_t checkErrorBuffer();

/**
 * @brief Register an error. Critical errors can be registered to the watchdog scratch register
 * 
 * @param source SW component generating the error
 * @param priority Registered error priority
 * @param errorCode Registered error code
 */
void registerError(Error_Source_e source, Error_Priority_e priority, uint32_t errorCode);

Error_Response_e handleError(Error_t error);

#endif