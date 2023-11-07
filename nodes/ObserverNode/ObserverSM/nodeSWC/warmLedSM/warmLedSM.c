#include "warmLedSM.h"
#include "../../../Observer_config.h"

#include "hardware/pwm.h"

typedef enum 
{
  UNINITIALIZED,
  NO_CHANGE,
  UPDATE,
  FAULT
} LED_State;

struct
{
    uint8_t     controlPin;
    uint8_t     slice_num;
    uint8_t     channel;

    uint8_t     polarity; /* Allow for both P and N channel PWM control */
    uint16_t    riseDelay_ns;
    uint16_t    riseTime_ns;
    uint16_t    fallDelay_ns;
    uint16_t    fallTime_ns;

    uint16_t    duty_cycle;
    uint16_t    divider;

    LED_State   ledState;
} warmLED_MOSFET_specs = 
{
  .controlPin   = COLD_LED_PWM_PIN,
  .polarity     = true,
  .riseDelay_ns = 5u,
  .riseTime_ns  = 14u,
  .fallDelay_ns = 4u,
  .fallTime_ns  = 30u,
  .ledState     = UNINITIALIZED
};

///TODO: calculate heat dissipation and brightness values derived from mosfet values

/* LED brightness interpolation values */
uint16_t warmLED_MOSFET_interp[] = 
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

uint8_t warmLED_MOSFET_interp_size = sizeof(warmLED_MOSFET_interp) / sizeof(uint16_t);

uint8_t warmLedSM_init()
{
  uint8_t retVal = 0;
  /* Calculate mosfet values */

  /* Initialize pwm functionality */
  gpio_set_function(COLD_LED_PWM_PIN, GPIO_FUNC_PWM);
  warmLED_MOSFET_specs.slice_num  = pwm_gpio_to_slice_num (COLD_LED_PWM_PIN);
  warmLED_MOSFET_specs.channel    = pwm_gpio_to_channel   (COLD_LED_PWM_PIN);
  warmLED_MOSFET_specs.duty_cycle = warmLED_MOSFET_interp [0];
  warmLED_MOSFET_specs.ledState   = UPDATE;

  return retVal;
}

uint8_t warmLedSM_run()
{
  uint8_t retVal = 0;
  switch(warmLED_MOSFET_specs.ledState)
  {
    case UNINITIALIZED:
      warmLED_MOSFET_specs.ledState = FAULT;
    break;
    
    case UPDATE:
      pwm_set_chan_level(
        warmLED_MOSFET_specs.slice_num, 
        warmLED_MOSFET_specs.channel, 
        warmLED_MOSFET_specs.duty_cycle
        );
      warmLED_MOSFET_specs.ledState = NO_CHANGE;
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
  warmLED_MOSFET_specs.duty_cycle = warmLED_MOSFET_interp[level];
  warmLED_MOSFET_specs.ledState   = UPDATE;
  return retVal;
}