#include "pushButtonSM.h"

/* Use quadrature encoder template */
#include "../../../picoOS/Templates/PushButtonSM/PushButtonSM.h"

#include "../../../LightSwitch_config.h"

bool        buttonState           = false;
bool        pushButton_updateFlag = false;
uint32_t    buttonTimePressed     = 0u   ;

pushButtonSM_type pushButtonSM = 
{
    .buttonPin          =  ENCODER_C_PIN,
    .pinPull            =  true,

    .debounceTimeC_us   =        100u * 1000u,
    .debounceTimeout_us =  5u * 1000u * 1000u,
    
    .buttonPressed      = &buttonState,
    .timePressed        = &buttonTimePressed,
    .prevButtonState    =  false,
    
    .pushButtonState    =  SM_PUSHBTN_UINITINIALIZED,
};

/* Local functions */

uint8_t init_pushButtonSM()
{
    uint8_t retVal = 0u;
    init_PushButtonSM(&(pushButtonSM));
    return retVal;
}

uint8_t run_pushButtonSM()
{
    ///TODO: add specific return values
    uint8_t retVal = 0u;
    run_PushButtonSM(&(pushButtonSM));
  
    if(SM_PUSHBTN_N_NONE != pushButtonSM.notificationFlag)
    {
        switch(pushButtonSM.notificationFlag)
        {
            case SM_PUSHBTN_N_UPDATE:
                pushButtonSM.notificationFlag = false;
                pushButton_updateFlag         = true;
                break;

            ///TODO: internal fault handling
            case SM_PUSHBTN_N_LOW_PRIO_ERROR:
                break;
            case SM_PUSHBTN_N_MEDIUM_PRIO_ERROR:
                break;
            case SM_PUSHBTN_N_HIGH_PRIO_ERROR:
                break;
            default:
                break;
        }
    }

  return retVal;
}

/* 
    Mentions:

    (1): assumming a (STARTED_FROM_FAULT) return, loop variable might be unnecessary
 */