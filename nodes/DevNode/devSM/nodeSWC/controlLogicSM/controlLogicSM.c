#include "controlLogicSM.h"

#include "../../../dev_config.h"

extern bool encoderPosition_updateFlag;
extern bool pushButton_updateFlag;
extern bool Frame_SWCdata_Updated;

/* Temporary_Values - replace after code logic is done*/


/* Temporary_Values - replace after code logic is done*/

typedef enum 
{
  NONE,
  PRESS,
  MULTI_PRESS,
  LONG_PRESS,
  ROTATE,

  UNKNOWN
} UserInput;
UserInput userInput = NONE;

enum
{
  OFF,
  WHITE,
  RGB,
  WHITE_RGB,


  NO_OF_STATES
} UI_state;

struct notificationFlags
{
  bool targetSwitchRequested         : 1;
  bool patternCustomizationRequested : 1;
  bool multipressRequested           : 1;
  bool pressRequested                : 1;
  bool encoderPosition_updated       : 1;
} localNotificationFlags = 
{
  .targetSwitchRequested         = false,
  .patternCustomizationRequested = false,
  .multipressRequested           = false,
  .encoderPosition_updated       = false,
};


extern bool     buttonState      ;
extern uint32_t buttonTimePressed;
extern uint8_t  encoderPosition  ;
extern uint8_t  white_intensity  ;
extern uint8_t  white_color      ;
extern uint8_t  rgb_pattern_index;
extern uint8_t  rgb_intensity    ;
extern uint8_t  rgb_setting_0    ;
extern uint8_t  rgb_setting_1    ;
extern uint8_t  rgb_setting_2    ;

bool        buttonState_old                     = false;

uint8_t     encoderPosition_old                 = 0u;
 int8_t     encoderDelta                        = 0u;

uint8_t     lastPatternIndex                    = 0u;
uint8_t     lastPatternModifier                 = 0u;

uint8_t     multipressCounter                   = 0u;

uint32_t    multipressTimeout = 0u;

uint32_t    uiCustomizationTimeout              = 0u;

/* Debug variables */
uint32_t    prevNotificationTime                = MS_TO_US(1000u);

///TODO: implement debug build functionality for UART/printf calls
///TODO: add blinking indicator for the mode selected
///TODO: add multiple tap functionality

/* Data input functionality */
static inline UserInput checkUpdate_pushButtonSM()
{
  UserInput retVal = UNKNOWN;

  if(buttonState_old != buttonState)
  /* Button state changed */
  {
    if(BUTTON_PRESSED == buttonState)
    /* Button pressed */
    {
      /* Press time registration handled by pushbutton sm */
    }
    else
    /* Button released */
    {
      if(buttonTimePressed >= MS_TO_US(SWITCH_TIME_MS)) 
      {/* Button pressed for SWITCH_TIME_MS */
        /* Set target switch request flag */
        localNotificationFlags.targetSwitchRequested = true;
      }
      else 
      {
        multipressTimeout = (time_us_32() + MULTITAP_TIMEOUT_MS);
        ++multipressCounter;
      }
    }
  }
  else
  if(
      (buttonState       != BUTTON_PRESSED   ) &&
      (buttonTimePressed <= multipressTimeout)
    )
  {
    if(1u < multipressCounter)
    {
      localNotificationFlags.multipressRequested = true;
      retVal = MULTI_PRESS;
    }
    else
    {
      localNotificationFlags.pressRequested = true;
      retVal = PRESS;
    }
    multipressCounter = 0u;
  }
  else
  /* Button state is not changed */
  {
    retVal = NONE;
  }
  return retVal;
}

static inline UserInput checkUpdate_encoderSM()
{
  UserInput retVal = UNKNOWN;
  if(true == encoderPosition_updateFlag)
  {
    encoderDelta               = (int8_t)(encoderPosition - encoderPosition_old);
    encoderPosition_updateFlag = false;
    Frame_SWCdata_Updated      = true;
    retVal                     = ROTATE;
  }
  else
  {
    /* no pattern update */
    retVal = NONE;
  }
  return retVal;
}

/* Data output functionality*/
static inline uint8_t output_RGB_strip()
{
  uint8_t retVal = 0;
  return retVal;
}

static inline uint8_t output_LED_strip()
{
  uint8_t retVal = 0;
  return retVal;
}

static inline uint8_t output_LED_ring ()
{
  uint8_t retVal = 0;
  return retVal;
}

static inline uint8_t UI_Substate_Off()
{
  uint8_t retVal = 0;
  // switch()
  return retVal;
}
static inline uint8_t UI_Substate_White()
{
  uint8_t retVal = 0;
  
  return retVal;
}
static inline uint8_t UI_Substate_White_RGB()
{
  uint8_t retVal = 0;
  return retVal;
}
static inline uint8_t UI_Substate_RGB()
{
  uint8_t retVal = 0;
  return retVal;
}

/* Logic inferance functionality */
static inline uint8_t processInputs()
{
  uint8_t retVal = 0;
  switch(UI_state)
  {
    case OFF:
      /*  */
      retVal = UI_Substate_Off();
      break;
    
    case WHITE:
      /*  */
      retVal = UI_Substate_White();
      break;

    case RGB:
      /*  */
      retVal = UI_Substate_RGB();
      break;
    
    case WHITE_RGB:
      retVal = UI_Substate_White_RGB();
      break;

    default:

      break;

  }
  
  return retVal;
}

/* State machine functionality */
uint8_t controlLogic_devSM_init()
{
  uint8_t retVal = 0;
  /* Check if all the SWC are initialized */
  return retVal;
}

uint8_t controlLogic_devSM_run()
{
  uint8_t retVal = 0u;

  /* Check for SWC updates */
  checkUpdate_encoderSM   ();
  checkUpdate_pushButtonSM();

  // infereOutputs           ();

  output_LED_ring         ();
  output_RGB_strip        ();
  output_LED_strip        ();

  /* Reset notification flags */
  // notificationFlags = { 0, 0, 0, 0, 0, 0 };
  
  return retVal;
}