#include "controlLogicSM.h"

#include "../../../dev_config.h"

/* Local types */
enum ControlledTarget_e /* (1) */
{
  LED_CONTROL,
  RGB_CONTROL,

  NO_OF_TARGETS
} target;

enum UI_state_e
{
  OFF,
  IDLE,
  MODIFY_INTENSITY,
  MODIFY_COLOR,
  MODIFY_PATTERN,

  NO_OF_STATES,
} UI_state;



/* Local Global Variables */
struct 
{
  bool targetSwitchRequested        :1;
  bool patternCustomizationRequested:1;
  bool lightToggleRequested         :1;
  bool encoderPosition_updated      :1; 
  bool encoderPushButton_updated    :1;
} 
notificationFlags = 
{
  .encoderPosition_updated       = false,
  .targetSwitchRequested         = false,
  .patternCustomizationRequested = false,
  .lightToggleRequested          = false,
  .encoderPushButton_updated     = false
};

bool        encoderPushButton_status_prev       = false;

uint8_t     encoderPosition_old                 = 0u;
uint8_t     encoderDelta                        = 0u;
uint8_t     lastPatternIndex                    = 0u;
uint8_t     lastPatternModifier                 = 0u;

uint32_t    encoderPushButton_timeOfPressing    = 0u;
uint32_t    encoderPushButton_timePressed       = 0u;
uint32_t    encoderPushButton_multipressTimeout = 0u;

uint32_t    uiCustomizationTimeout              = 0u;

/* Debug variables */
uint32_t    prevNotificationTime                = MS_TO_US(1000u);

///TODO: implement debug build functionality for UART/printf calls
///TODO: add blinking indicator for the mode selected
///TODO: add multiple tap functionality

/* Data input functionality */
static inline uint8_t checkUpdate_pushButtonSM()
{
  if(encoderPushButton_status_prev != encoderPushButton_status)               /* Button state changed */
  {
    if(BUTTON_PRESSED == encoderPushButton_status)                            /* Button pressed */
    {
      encoderPushButton_timeOfPressing = time_us_32();                        /* Reset pressed timer */
    }
    else                                                                      /* Button released */
    {/* Check the pressed time, highest to lowest */
      if      (MS_TO_US(SWITCH_TIME_MS)    <= encoderPushButton_timePressed)  /* Button pressed for SWITCH_TIME_MS */
      {/* Switch light control */
        notificationFlags.targetSwitchRequested = true;                       /*  */
      }
      else if (MS_TO_US(CUSTOMIZE_PATTERN_TIME_MS) <= encoderPushButton_timePressed)  /* Button pressed for CUSTOMIZE_TIME_MS */
      {/* Customize pattern */
        notificationFlags.patternCustomizationRequested = true;               /* Local customization request */
      }
      else                                                                    /*  */
      {/* Turn off */
        notificationFlags.lightToggleRequested = true;                        /* Local lights off request */
      }
    }
  }
  else if(BUTTON_PRESSED == encoderPushButton_status)                         /* The button is continuously pressed */
  {
    ///TODO: add timer functionality
    encoderPushButton_timePressed = (time_us_32() - encoderPushButton_timeOfPressing);
    notificationFlags.encoderPosition_updated = true;
  }
  else
  {
    /* Button is not pressed */
  }
}

static inline uint8_t checkUpdate_encoderSM()
{
  if(encoderPosition_old != encoderPosition)
  {
    /* uint8 data type ensures wrap around the value 255 */
    encoderDelta            =(encoderPosition_old - encoderPosition);
    encoderPosition_old     = encoderPosition; 
    notificationFlags.encoderPosition_updated = true;
  }
  else
  {
    /* no pattern update */
  }
}

/* Data output functionality*/
static inline uint8_t output_RGB_strip()
{

}

static inline uint8_t output_LED_strip()
{

}

static inline uint8_t output_LED_ring ()
{

}

/* Logic inferance functionality */
static inline uint8_t infereOutputs()
{
  switch(UI_state)
  {
    case OFF: /* Lights are off */
      if(true == notificationFlags.lightToggleRequested)                  /* A request turning on the light has been issued */
      {
        switch(target)                                                    /* determine last used light type */
        {
          case LED_CONTROL:                                               /* last light type was an RGB pattern */
            output_LED_strip(TURN_ON);
          break;

          case RGB_CONTROL:                                               /* last light type was white LED light */
            output_RGB_strip(TURN_ON);
          break;

          default:
            ///TODO: add error handling
          break;
        }

        notificationFlags.lightToggleRequested = false;                   /* Acknowledge request */

      }
      else                                                                /* No request has been issued */
      {
        /* No other updates are necessary */
      }
    break;

    case IDLE:
      if      (true == notificationFlags.lightToggleRequested)            /* A request for turning off the light was issued */
      {
        switch(target) /* determine active light type */
        {
          case LED_CONTROL: /* last light type is an RGB pattern */
            output_LED_strip(TURN_OFF);
          break;

          case RGB_CONTROL: /* last light type is white LED light */
            output_RGB_strip(TURN_OFF);
          break;

          default:
            ///TODO: add error handling
          break;
        }

        notificationFlags.lightToggleRequested = false;

      }
      else if (true == notificationFlags.targetSwitchRequested)
      {
        switch(target) /* determine active light type */
        {
          case LED_CONTROL: /* last light type is an RGB pattern */
            output_LED_strip(TURN_OFF);
            output_RGB_strip(TURN_ON);
            target = RGB_CONTROL;
          break;

          case RGB_CONTROL: /* last light type is white LED light */
            output_RGB_strip(TURN_OFF);
            output_LED_strip(TURN_ON);
            target = LED_CONTROL;
          break;

          default:
            ///TODO: add error handling
          break;
        }
      }
      else if (true == notificationFlags.patternCustomizationRequested)
      {
        UI_state = MODIFY_INTENSITY;
        uiCustomizationTimeout = time_us_32() + CUSTOMIZATION_TIMEOUT;
      }
    break;

    case MODIFY_INTENSITY:
    break;

    case MODIFY_COLOR:
      if(time_us_32() <= uiCustomizationTimeout)
      {

      }
      else if()
      {
        
      }
      else
      {
        UI_state = IDLE;
      }
    break;

    case MODIFY_PATTERN:
      if(time_us_32() <= uiCustomizationTimeout)
      {

      }
      else if()
      {

      }
      else
      {
        UI_state = IDLE;
      }
    break;
  }

  /* 
  Light switching logic

    Initial state:  LED_off
    Press:          turn on last pattern (rgb/white)
    Double Press:   no effect
    Long   Press:   no effect
    Rotate:         no effect
    
    Initial state:  White_Pattern
    Press:          Change to (LED_off)
    Double Press:   Change to (Select_white_pattern)
    Long   Press:   Change to (RGB_Pattern)
    Rotate:         Change intensity - <send update message>

    Initial state:  RGB_Pattern
    Press:          Change to (LED_off)
    Double Press:   Change to (Select_RGB_pattern)
    Long   Press:   Change to (White_Pattern)
    Rotate:         Change intensity - <send update message>

    Initial state:  Select_RGB_pattern
    Press:          Change to (RGB_Pattern) -   <save settings>
    Double Press:   No effect
    Long   Press:   No effect
    Rotate:         Change pattern - <update local RGB ring>

    Initial state:  Select_white_pattern
    Press:          Change to (White_Pattern) - <save settings>
    Double Press:   No effect
    Long   Press:   No effect
    Rotate:         Change pattern - <send update message>
   */
}

/* State machine functionality */
uint8_t controlLogic_devSM_init()
{
  /* Check if all the SWC are initialized */
}

uint8_t controlLogic_devSM_run()
{
  uint8_t retVal;

  /* Update Flags */
  bool updateRGB_strip = false;
  bool updateLED_strip = false;
  bool updateRGB_ring  = false;

  /* Check for SWC updates */
  checkUpdate_encoderSM   ();
  checkUpdate_pushButtonSM();

  infereOutputs           ();

  output_LED_ring         ();
  output_RGB_strip        ();
  output_LED_strip        ();

  /* Reset notification flags */
  notificationFlags = {0,0,0,0,0};
}

/* Mentions:
    (1) target data type is best left node specific, as to allow user customization
 */

/* Explanations: 

