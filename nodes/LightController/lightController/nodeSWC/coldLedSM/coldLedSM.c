#include "coldLedSM.h"
#include "../../../LightController_config.h"
#include "../../../picoOS/Templates/fetControl/fetControl.h"
#include "hardware/pwm.h"

#include <stdio.h>

/* IPC variables */

uint8_t received_coldWhiteIntensity;
extern uint8_t current_coldWhiteIntensity;

enum LED_SM_State
{
  UNINITIALIZED,
  NO_CHANGE,
  UPDATE,
  FAULT
} coldLedState = UNINITIALIZED;

/* LED brightness interpolation values */
uint16_t coldLED_MOSFET_dutyCycles[] = 
{
  0,      /* fully off */
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

Pulsed_FET_specs coldLED_MOSFET_specs = 
{
  .controlPin           = COLD_LED_PWM_PIN          ,
  .polarity             = COLD_LED_PWM_POLARITY     ,
  
  .riseDelay_ns         = COLD_LED_PWM_RISE_DELAY_NS,
  .riseTime_ns          = COLD_LED_PWM_RISE_TIME_NS ,
  .fallDelay_ns         = COLD_LED_PWM_FALL_DELAY_NS,
  .fallTime_ns          = COLD_LED_PWM_FALL_TIME_NS ,

  .driver_riseDelay_ns  = COLD_LED_PWM_DRIVER_RISE_DELAY_NS,
  .driver_riseTime_ns   = COLD_LED_PWM_DRIVER_RISE_TIME_NS ,
  .driver_fallDelay_ns  = COLD_LED_PWM_DRIVER_FALL_DELAY_NS,
  .driver_fallTime_ns   = COLD_LED_PWM_DRIVER_FALL_TIME_NS ,

  .dutyCycles           = coldLED_MOSFET_dutyCycles ,
  .discreeteLevels      = sizeof(coldLED_MOSFET_dutyCycles) / sizeof(coldLED_MOSFET_dutyCycles[0])
};

void coldLedSM_Init()
{
  /* Calculate mosfet values */

  init_pulsed_fetControl(&coldLED_MOSFET_specs);

  /* Initialize pwm functionality */
  gpio_set_function(COLD_LED_PWM_PIN, GPIO_FUNC_PWM);
  coldLED_MOSFET_specs.slice_num  = pwm_gpio_to_slice_num (COLD_LED_PWM_PIN);
  coldLED_MOSFET_specs.channel    = pwm_gpio_to_channel   (COLD_LED_PWM_PIN);
  coldLED_MOSFET_specs.currentDutyCycle = coldLED_MOSFET_dutyCycles [0];
  coldLedState = UPDATE;
}

void coldLedSM_Run   ()
{

}

void coldLedSM_Update()
{

}