#include "pushButtonSM.h"

/* Use quadrature encoder template */
#include "../../../picoOS/Templates/PushButtonSM/PushButtonSM.h"

#include "../../../ledTester_config.h"

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

uint8_t pushButtonSM_init()
{
  uint8_t retVal = 0u;
  init_PushButtonSM(&(pushButtonSM));
  return retVal;
}

uint8_t pushButtonSM_run()
{
  ///TODO: add specific return values
  uint8_t retVal = 0u;
  run_PushButtonSM(&(pushButtonSM));
  
  if(pushButtonSM.notificationFlag != SM_PUSHBTN_N_NONE)
  {
    switch(pushButtonSM.notificationFlag)
    {
      case SM_PUSHBTN_N_UPDATE:
        pushButtonSM.notificationFlag = false;
        pushButton_updateFlag         = true;
        
        printf("Push Button state updated to: %d\n",   buttonState);
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