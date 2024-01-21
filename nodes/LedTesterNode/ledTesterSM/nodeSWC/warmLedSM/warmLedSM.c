#include "warmLedSM.h"
#include "../../../ledTester_config.h"
#include "../../../picoOS/Templates/fetControl/fetControl.h"

typedef enum 
{
  UNINITIALIZED,
  NO_CHANGE,
  UPDATE,
  FAULT
} LED_SM_State;

LED_SM_State warmLedState = UNINITIALIZED;

///TODO: calculate heat dissipation and brightness values derived from mosfet values

/* LED brightness interpolation values */
uint16_t warmLED_MOSFET_dutyCycles[] = 
{
  0,      /* Initial value */
  3600,   /* min value */
  6800,
  9600,
  16000,
  26000,
  33000,
  44000,
  53000,
  65535   /* fully on */
};

Pulsed_FET_specs warmLED_MOSFET_specs = 
{
  .controlPin           = WARM_LED_PWM_PIN          ,
  .polarity             = WARM_LED_PWM_POLARITY     ,
  
  .riseDelay_ns         = WARM_LED_PWM_RISE_DELAY_NS,
  .riseTime_ns          = WARM_LED_PWM_RISE_TIME_NS ,
  .fallDelay_ns         = WARM_LED_PWM_FALL_DELAY_NS,
  .fallTime_ns          = WARM_LED_PWM_FALL_TIME_NS ,

  .driver_riseDelay_ns  = WARM_LED_PWM_DRIVER_RISE_DELAY_NS,
  .driver_riseTime_ns   = WARM_LED_PWM_DRIVER_RISE_TIME_NS ,
  .driver_fallDelay_ns  = WARM_LED_PWM_DRIVER_FALL_DELAY_NS,
  .driver_fallTime_ns   = WARM_LED_PWM_DRIVER_FALL_TIME_NS ,

  .dutyCycles           = warmLED_MOSFET_dutyCycles ,
  .discreeteLevels      = sizeof(warmLED_MOSFET_dutyCycles) / sizeof(warmLED_MOSFET_dutyCycles[0])
};


uint8_t warmLedSM_init()
{
  uint8_t retVal = 0;
  warmLedState         = UPDATE;

  return retVal;
}

uint8_t warmLedSM_run()
{
  uint8_t retVal = 0;
  switch(warmLedState)
  {
    case UNINITIALIZED:
      warmLedState = FAULT;
    break;
    
    case UPDATE:
      pwm_set_chan_level(
        warmLED_MOSFET_specs.slice_num, 
        warmLED_MOSFET_specs.channel, 
        warmLED_MOSFET_specs.currentDutyCycle
        );
      warmLedState = NO_CHANGE;
    break;
    
    case NO_CHANGE:
      
    break;

    case FAULT:
      
    break;
  }

  return retVal;
}

uint8_t warmLedSM_update(uint8_t level)
{
  uint8_t retVal = 0;
  warmLED_MOSFET_specs.currentDutyCycle = warmLED_MOSFET_dutyCycles[level];
  warmLedState   = UPDATE;
  return retVal;
}