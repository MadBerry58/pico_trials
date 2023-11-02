#ifndef DEV_PUSH_BUTTON_SM
#define DEV_PUSH_BUTTON_SM

#include "pico/stdlib.h"

/* PushButtonSM types */
typedef enum 
{
    UINITINIALIZED,
    INITIALIZED,
    RELEASED,
    PRESS_DEBOUNCE,
    PRESSED,
    RELEASE_DEBOUNCE,

    FAULT
} PushButtonState;

typedef struct
{
    bool            pinPull;                /* SM pin polarity (pull up or down) */
    uint8_t         buttonPin;              /* The button pin */
    uint32_t        debounceTimeC_us;       /* Debounce time calibration between states */

    PushButtonState pushButtonState;        /* State machine state */
    
    bool            buttonPressed;          /* Output variable for button state */
    
    bool            prevButtonState;        /* SM-local previous state variable*/
    uint32_t        debounceTimeout_us;     /* SM-local momentary debounce timeout value */
} pushButtonSM_type;

uint8_t pushButtonSM_init();

uint8_t pushButtonSM_run();

#endif