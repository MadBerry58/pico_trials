#ifndef PUSH_BUTTON_SM_TEMPLATE_H
#define PUSH_BUTTON_SM_TEMPLATE_H

#include <stdio.h>
#include "pico/stdlib.h"

/* PushButtonSM types */
typedef enum 
{
    SM_PUSHBTN_UINITINIALIZED,
    SM_PUSHBTN_INITIALIZED,
    SM_PUSHBTN_RELEASED,
    SM_PUSHBTN_PRESS_DEBOUNCE,
    SM_PUSHBTN_PRESSED,
    SM_PUSHBTN_RELEASE_DEBOUNCE,

    SM_PUSHBTN_FAULT
} PushButtonState;

typedef enum
{
    SM_PUSHBTN_N_NONE,
    SM_PUSHBTN_N_UPDATE,

    /* Errors are arranged in increasing order */
    SM_PUSHBTN_N_LOW_PRIO_ERROR,
    SM_PUSHBTN_N_MEDIUM_PRIO_ERROR,
    SM_PUSHBTN_N_HIGH_PRIO_ERROR
} pushbutton_sm_notificationType;

typedef enum
{
    SM_PUSHBTN_E_NONE,
    SM_PUSHBTN_E_UNITINIALIZED
} pushbutton_sm_errorType;

typedef struct
{
    uint8_t                         buttonPin;              /* The button pin */

    bool                            pinPull;                /* SM pin polarity (pull up or down) */
    uint32_t                        debounceTimeC_us;       /* Debounce time calibration between states */

    PushButtonState                 pushButtonState;        /* State machine state */
    
    bool                           *buttonPressed;          /* Output variable for button state */
    uint32_t                       *timePressed;            /* Time the button was pressed */
    
    bool                            prevButtonState;        /* SM-local previous state variable*/
    uint32_t                        timeOfPressing;         /* Time the button was pressed */
    uint32_t                        debounceTimeout_us;     /* SM-local momentary debounce timeout value */
    pushbutton_sm_notificationType  notificationFlag;  
} pushButtonSM_type;

uint8_t init_PushButtonSM(pushButtonSM_type *pushButtonSM);
uint8_t  run_PushButtonSM(pushButtonSM_type *pushButtonSM);

#endif