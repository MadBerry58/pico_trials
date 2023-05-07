#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#define ERROR_BUFFER_SIZE 16u

#include <stdio.h>

typedef enum {
    E_CRITICAL,
    E_SEVERE,
    E_MODERATE,
    E_LOW,
    E_NONE
} Error_Priority_e;


typedef enum 
{
    E_S_OS,
    E_S_LIGHT_SWITCH,
    E_S_LIGHT_CONTROLLER,
    E_S_WINDOW_CONTROLLER,
    E_S_RADIATOR_CONTROLLER
} Error_Source_e;


typedef enum {
    OS_E_OK,
    OS_E_NOK,
    OS_E_WATCHDOG,
    OS_E_COMM_NO_ACK,
    OS_E_COMM_ID_MISMATCH,
    OS_E_COMM_ROLE_MISMATCH,
    OS_E_COMM_FAILED,
    OS_E_CRYPT_INVALID
} Errors_OS_e;

typedef enum {
    LS_E_OK,
    LS_E_NOK,
    LS_E_ENCODER,
    LS_E_RGB_PREVIEW
} Errors_LightSwitch_e;

typedef enum {
    LC_E_OK,
    LC_E_NOK,
    LS_E_RGB_PATTERN,
    LS_E_WHITE_WARM,
    LS_E_WHITE_COLD
} Error_LightControl_e;

typedef enum {
    MC_E_OK,
    MC_E_NOK,
    MC_E_SENSORFAILURE,
    MC_E_MOTORFAILURE
} Error_MotorControl_e;

typedef enum {
    E_R_CONTINUE,
    E_R_PAUSE,
    E_R_SAFE_REBOOT,
    E_R_IMEDIATE_REBOOT,
    E_R_SAFE_MODE
} Error_Response_e;

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