#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#define ERROR_BUFFER_SIZE 16u

#include <stdio.h>
#include "pico/stdlib.h"

typedef enum Error_Priority{
    E_CRITICAL,
    E_SEVERE,
    E_MODERATE,
    E_LOW,
    E_NONE,
};


typedef enum Error_Source{
    E_S_OS,
    E_S_LIGHT_SWITCH,
    E_S_LIGHT_CONTROLLER,
    E_S_WINDOW_CONTROLLER,
    E_S_RADIATOR_CONTROLLER
};


typedef enum Errors_OS{
    OS_E_OK,
    OS_E_NOK,
    OS_E_WATCHDOG,
    OS_E_COMM_NO_ACK,
    OS_E_COMM_ID_MISMATCH,
    OS_E_COMM_ROLE_MISMATCH,
    OS_E_COMM_FAILED,
    OS_E_CRYPT_INVALID
};

typedef enum Errors_LightSwitch{
    LS_E_OK,
    LS_E_NOK,
    LS_E_ENCODER,
    LS_E_RGB_PREVIEW
};

typedef enum Error_LightControl{
    LC_E_OK,
    LC_E_NOK,
    LS_E_RGB_PATTERN,
    LS_E_WHITE_WARM,
    LS_E_WHITE_COLD
};

typedef enum Error_MotorControl{
    MC_E_OK,
    MC_E_NOK,
    MC_E_SENSORFAILURE,
    MC_E_MOTORFAILURE
};

typedef enum Error_Response{
    E_R_CONTINUE,
    E_R_PAUSE,
    E_R_SAFE_REBOOT,
    E_R_IMEDIATE_REBOOT,
    E_R_SAFE_MODE
};

typedef struct Error_t{
    unsigned int   error_code;
    Error_Source   source;
    Error_Priority priority;
    Error_Response response;
};



/**
 * @brief Retrieve next highest priority from error buffer
 * 
 * @return Error_t 
 *//
Error_t checkErrorBuffer();

/**
 * @brief Register an error. Critical errors can be registered to the watchdog scratch register
 * 
 * @param source SW component generating the error
 * @param priority Registered error priority
 * @param errorCode Registered error code
 *//
void registerError(Error_Source source, Error_Priority priority, uint32_t errorCode);

Error_Response handleError(Error_t error);

#endif