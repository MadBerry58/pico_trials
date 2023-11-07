#include "pushButtonSM.h"
#include "../../../Observer_config.h"
///TODO: move entire code to template folder
///TODO: move declarations to config header

/* Local functions */

uint8_t pushButtonSM_init(pushButtonSM_type sm)
{
  uint8_t retVal;
  /* initialize gpio pin */
  gpio_init   (sm.buttonPin);
  gpio_set_dir(sm.buttonPin, GPIO_IN);

  if(true == sm.pinPull)                                  /* pin is pulled up */
  {
    gpio_pull_up    (sm.buttonPin);                       /* pull pin up to 3.3v */
    gpio_set_inover (sm.buttonPin, GPIO_OVERRIDE_INVERT); /* set pressed state as pin low */
  }
  else                                                    /* pin is pulled down */
  {
    gpio_pull_down  (sm.buttonPin);                       /* pull pin down to 0v */
    gpio_set_inover (sm.buttonPin, GPIO_OVERRIDE_NORMAL); /* set pressed state as pin high */
  }

  if(true == gpio_get(sm.buttonPin))                      /* Check for shorted contacts */
  {
    sm.pushButtonState = FAULT;                           /* Set SM state to FAULT */
    retVal = 2;                                           /* Return pin_shorted error */
  }
  else
  {
    retVal = 0;                                           /* Set unknown state return */
    sm.pushButtonState = RELEASED;                        /* Set SM state to INITIALIZED */
  }

  return retVal;
}

uint8_t pushButtonSM_run(pushButtonSM_type sm)
{
  ///TODO: add specific return values
  uint8_t retVal;

  bool loop = true; //(1)

  while(loop)
  {
    switch(sm.pushButtonState)                            /* Switch state machine behavior */
    {
      /** SM was not correctly initialized **/
      case UINITINIALIZED:
        sm.pushButtonState        = FAULT;                /* Set SM state to FAULT */
        retVal                    = 2;                    /* Return SM_uninitialized error */
      break;

      /** Push Button output set to RELEASED **/
      case RELEASED:
        if(true == gpio_get(sm.buttonPin))                /* Button pressed */
        {
          sm.debounceTimeout_us   = (time_us_32() +       /* Initiate debounce timeout value */
                                    sm.debounceTimeC_us);
          sm.pushButtonState      = PRESS_DEBOUNCE;       /* Set SM state to PRESS_DEBOUNCE */
          retVal                  = 0u;                   /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else                                              /* Button was not pressed */
        {
          sm.pushButtonState = RELEASED;                  /* Remain in RELEASED state */
          retVal                  = 0u;                   /* No error return */
          loop                    = false;                /* Exit sm */
        }
      break;

      /** GPIO state switched to ON **/
      case PRESS_DEBOUNCE:
        if( 
            (time_us_32() <= sm.debounceTimeC_us    ) &&  /* Timer not expired */
            (true         == gpio_get(sm.buttonPin) )     /* Button is pressed */
          )
        {                                                 /* Button debouncing */
          sm.pushButtonState      = PRESS_DEBOUNCE;       /* Remain in PRESS_DEBOUNCE state */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else
        if(true == gpio_get(sm.buttonPin))                /* Button pressed and timer expired */
        {
          sm.debounceTimeout_us   = UINT32_MAX;           /* Reset debounce timer */
          sm.pushButtonState      = PRESSED;              /* Set SM state to PRESSED */
          sm.buttonPressed        = true;                 /* Update output*/
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else                                              /* Button released before debounce */
        {
          sm.debounceTimeout_us   = UINT32_MAX;           /* Reset debounce timer */
          sm.pushButtonState      = RELEASED;             /* Return to RELEASED state */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
      break;

      /** Push Button output set to PRESSED **/
      case PRESSED:
        if(false == gpio_get(sm.buttonPin))               /* Pin state changed to RELEASED */
        {
          sm.debounceTimeout_us   = (time_us_32() +       /* Initiate debounce timeout value */
                                    sm.debounceTimeC_us);
          sm.pushButtonState      = RELEASE_DEBOUNCE;     /* Set SM state to RELEASE_DEBOUNCE */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else                                              /* Pin state is still PRESSED */
        {
          sm.pushButtonState      = PRESSED;              /* Remain in PRESSED state */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
      break;

      /** GPIO state switched to OFF **/
      case RELEASE_DEBOUNCE:
        if(
            (time_us_32() <= sm.debounceTimeout_us ) &&   /* Timer not expired */
            (false        == gpio_get(sm.buttonPin))      /* Button released */
          )
        {                                                 /* Button debouncing */
          sm.pushButtonState      = RELEASE_DEBOUNCE;     /* Remain in PRESSED state */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else
        if(false == gpio_get(sm.buttonPin))               /* Button released and timer expired */
        {
          sm.debounceTimeout_us   = UINT32_MAX;           /* Reset debounce timer */
          sm.pushButtonState      = RELEASED;             /* Set SM state to RELEASED */
          sm.buttonPressed        = true;                 /* Update output*/
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
        else                                              /* Button released before debounce */
        {
          sm.debounceTimeout_us   = UINT32_MAX;           /* Reset debounce timer */
          sm.pushButtonState      = PRESSED;              /* Return to PRESSED state */
          retVal                  = 0;                    /* No error return */
          loop                    = false;                /* Exit sm */
        }
      break;

      /* Fault handling */
      case FAULT:
        sm.pushButtonState        = FAULT;                /* Set SM state to FAULT */
        sm.buttonPressed          = false;                /* Reset output*/
        // retVal = 1;                                    /* Return last error set */
        loop                      = false;                /* Exit sm */
      break;
      
      /* Unknown state handling */
      default:                                            /* Unknown state */
        sm.pushButtonState        = FAULT;                /* Set SM state to FAULT */
        retVal                    = 1;                    /* Set unknown state return */
        loop                      = true;                 /* Transition to FAULT state */
      break;
    }
  }
  return retVal;
}

/* 
    Mentions:

    (1): assumming a (STARTED_FROM_FAULT) return, loop variable might be unnecessary
 */