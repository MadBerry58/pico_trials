#include "warmLedSM.h"
#include "../../../LightController_config.h"
#include "../../../picoOS/Templates/fetControl/fetControl.h"
#include "hardware/pwm.h"

#include <stdio.h>

/* IPC variables */
extern uint8_t received_warmWhiteIntensity;

/* SWC specific types */
enum LED_SM_State
{
  UNINITIALIZED,
  NO_CHANGE,
  UPDATE,
  FAULT
} warmLedState = UNINITIALIZED;

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

extern uint8_t current_warmWhiteIntensity;

void warmLedSM_Init   ()
{

}

void warmLedSM_Run    ()
{

}

void warmLedSM_Update ()
{

}
