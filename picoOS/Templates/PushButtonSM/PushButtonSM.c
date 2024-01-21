#include "PushButtonSM.h"
#include "hardware/gpio.h"

uint8_t init_PushButtonSM(pushButtonSM_type *pushButtonSM)
{
  uint8_t retVal= 0;
  /* initialize gpio pin */
  gpio_init   (pushButtonSM->buttonPin);
  gpio_set_dir(pushButtonSM->buttonPin, GPIO_IN);

  if(true == pushButtonSM->pinPull)                                   /* pin is pulled up */
  {
    gpio_pull_up    (pushButtonSM->buttonPin);                        /* pull pin up to 3.3v */
    gpio_set_inover (pushButtonSM->buttonPin, GPIO_OVERRIDE_INVERT);  /* set pressed state as pin low */
  }
  else                                                                /* pin is pulled down */
  {
    gpio_pull_down  (pushButtonSM->buttonPin);                        /* pull pin down to 0v */
    gpio_set_inover (pushButtonSM->buttonPin, GPIO_OVERRIDE_NORMAL);  /* set pressed state as pin high */
  }

  if(true == gpio_get(pushButtonSM->buttonPin))                       /* Check for shorted contacts */
  {
    pushButtonSM->pushButtonState = SM_PUSHBTN_FAULT;                 /* Set SM state to FAULT */
    retVal = 2;                                                       /* Return pin_shorted error */
  }
  else
  {
    retVal = 0;                                                       /* Set unknown state return */
    pushButtonSM->pushButtonState = SM_PUSHBTN_RELEASED;              /* Set SM state to INITIALIZED */
  }

  return retVal;
}

uint8_t run_PushButtonSM(pushButtonSM_type *pushButtonSM)
{
  bool loop = true; //(1)
  pushButtonSM->notificationFlag = SM_PUSHBTN_N_NONE;
  uint8_t retVal = 0;
  ///TODO: add error notification flags output

  while(loop)
  {
    /* Switch state machine behavior */
    switch(pushButtonSM->pushButtonState)
    {
      /** SM was not correctly initialized **/
      case SM_PUSHBTN_UINITINIALIZED:
        /* Set SM state to FAULT, Return SM_uninitialized error */
        pushButtonSM->pushButtonState       = SM_PUSHBTN_FAULT;
        pushButtonSM->notificationFlag      = SM_PUSHBTN_N_HIGH_PRIO_ERROR;
        retVal                              = SM_PUSHBTN_E_UNITINIALIZED;
      break;

      /** Push Button output set to RELEASED **/
      case SM_PUSHBTN_RELEASED:
        if(true == gpio_get(pushButtonSM->buttonPin))
        /* Button pressed */
        {
          /* Initiate debounce timeout value */
          pushButtonSM->debounceTimeout_us  = (time_us_32() + pushButtonSM->debounceTimeC_us);
          /* Transition to state PRESS_DEBOUNCE, No error return, Exit sm */
          pushButtonSM->pushButtonState     = SM_PUSHBTN_PRESS_DEBOUNCE;
          retVal                            = SM_PUSHBTN_E_NONE;
          loop                              = false;
        }
        else
        /* Button was not pressed */
        {
          /* Remain in RELEASED state, No error return, Exit sm */
          pushButtonSM->pushButtonState     = SM_PUSHBTN_RELEASED;
          retVal                            = SM_PUSHBTN_E_NONE;
          loop                              = false;
        }
      break;

      /** GPIO state switched to ON **/
      case SM_PUSHBTN_PRESS_DEBOUNCE:
        if( 
            (time_us_32() <= pushButtonSM->debounceTimeC_us    ) &&
            (true         == gpio_get(pushButtonSM->buttonPin) )
          )
        /* Button is pressed, debounce timer not expired */
        {
          /* Remain in PRESS_DEBOUNCE state, No error return, Exit sm */
          pushButtonSM->pushButtonState     = SM_PUSHBTN_PRESS_DEBOUNCE;
          retVal                            = SM_PUSHBTN_E_NONE;
          loop                              = false;
        }

        else
        if(true == gpio_get(pushButtonSM->buttonPin))
        /* Button pressed, debounce timer expired */
        {
          /* Reset debounce timer */
          pushButtonSM->debounceTimeout_us  = UINT32_MAX;

          /* Update output*/
        *(pushButtonSM->buttonPressed)      = true;
          /* Update timing data */
        *(pushButtonSM->timePressed)        = 0;
          pushButtonSM->timeOfPressing      = time_us_32();
          /* Set notification flag */
          pushButtonSM->notificationFlag    = SM_PUSHBTN_N_UPDATE;

          /* Set SM state to PRESSED, No error return, Exit sm */
          pushButtonSM->pushButtonState     = SM_PUSHBTN_PRESSED;
          retVal                            = SM_PUSHBTN_E_NONE;
          loop                              = false;
        }
        else
        /* Button released before debounce */
        {
          /* Reset debounce timer */
          pushButtonSM->debounceTimeout_us  = UINT32_MAX;

          /* Return to RELEASED state, No error return, Exit sm */
          pushButtonSM->pushButtonState     = SM_PUSHBTN_RELEASED;  
          retVal                            = SM_PUSHBTN_E_NONE;
          loop                              = false;
        }
      break;

      /** Push Button output set to PRESSED **/
      case SM_PUSHBTN_PRESSED:
        if(false == gpio_get(pushButtonSM->buttonPin)) 
        /* Pin state changed to RELEASED */
        {
          /* Initiate debounce timeout value */
          pushButtonSM->debounceTimeout_us   = (time_us_32() + pushButtonSM->debounceTimeC_us);

          /* Set SM state to RELEASE_DEBOUNCE, No error return, Exit sm */
          pushButtonSM->pushButtonState      = SM_PUSHBTN_RELEASE_DEBOUNCE;
          retVal                             = SM_PUSHBTN_E_NONE;
          loop                               = false;
        }
        else
        /* Pin state is still PRESSED */
        {
          /* Update pressed time */
        *(pushButtonSM->timePressed)         = ((time_us_32() - pushButtonSM->timeOfPressing));

          /* Remain in PRESSED state, No error return, Exit sm */
          pushButtonSM->pushButtonState      = SM_PUSHBTN_PRESSED;
          retVal                             = SM_PUSHBTN_E_NONE;
          loop                               = false;
        }
      break;

      /** GPIO state switched to OFF **/
      case SM_PUSHBTN_RELEASE_DEBOUNCE:
        if(
            (time_us_32() <= pushButtonSM->debounceTimeout_us ) && 
            (false        == gpio_get(pushButtonSM->buttonPin))
          )
        /* Button released, Timer not expired */
        {
          /* Remain in RELEASE_DEBOUNCE state, No error return, Exit sm */
          pushButtonSM->pushButtonState      = SM_PUSHBTN_RELEASE_DEBOUNCE;
          retVal                             = SM_PUSHBTN_E_NONE;
          loop                               = false;
        }

        else
        if(false == gpio_get(pushButtonSM->buttonPin))
        /* Button released and timer expired */
        {
          /* Reset debounce timer */
          pushButtonSM->debounceTimeout_us   = UINT32_MAX;

          /* Update output */
        *(pushButtonSM->buttonPressed)       = false;
        *(pushButtonSM->timePressed)         = 0;
          pushButtonSM->notificationFlag     = SM_PUSHBTN_N_UPDATE;

          /* Set SM state to RELEASED, No error return, Exit sm */
          pushButtonSM->pushButtonState      = SM_PUSHBTN_RELEASED;
          retVal                             = SM_PUSHBTN_E_NONE;
          loop                               = false;
        }

        else
        /* Button pressed before debounce */
        {
          /* Reset debounce timer */
          pushButtonSM->debounceTimeout_us   = UINT32_MAX;

          /* Return to PRESSED state, No error return, Exit sm */
          pushButtonSM->pushButtonState      = SM_PUSHBTN_PRESSED;
          retVal                             = SM_PUSHBTN_E_NONE;
          loop                               = false;
        }
      break;

      /* Fault handling */
      case SM_PUSHBTN_FAULT:
        /* Set SM state to FAULT */
        pushButtonSM->pushButtonState        = SM_PUSHBTN_FAULT;

        /* Reset output*/
      *(pushButtonSM->buttonPressed)         = false;
      *(pushButtonSM->timePressed)           = 0;

        /* Preserve last error set, Preserve error notification value, Exit sm */
        loop                                 = false;
      break;
      
      /* Unknown state handling */
      default:
        /* Set SM state to FAULT, Set unknown state return, Transition to FAULT state */
        pushButtonSM->pushButtonState        = SM_PUSHBTN_FAULT;
        retVal                               = 1;
        loop                                 = true;
      break;
    }
  }
  return retVal;
}