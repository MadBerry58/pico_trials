#include "coldLedSM.h"
#include "../../../ledTester_config.h"
#include "../../../picoOS/Templates/fetControl/fetControl.h"

extern uint8_t white_intensity;
       uint8_t current_white_intensity_index;

typedef enum 
{
  UNINITIALIZED,
  RUNNING,
  STOPPED,
  FAULT
}
LED_SM_State;

LED_SM_State coldLedState = UNINITIALIZED;

/* LED brightness interpolation values */
uint16_t coldLED_MOSFET_dutyCycles[] = 
{
  0,      /* fully off */
  1,   /* min value */
  2,
  4,
  8,
  16,
  32,
  64,
  128,
  256,
  512,
  1024,
  2048,
  4096,
  8192,
  16384,
  32768,
  65535   /* fully on */
};

Pulsed_FET_specs coldLED_MOSFET_specs = 
{
  .controlPin           = COLD_LED_PWM_PIN          ,
  .polarity             = COLD_LED_PWM_POLARITY     ,
  .frequency_kHz        = 1000u,
  
  .riseDelay_ns         = COLD_LED_PWM_RISE_DELAY_NS,
  .riseTime_ns          = COLD_LED_PWM_RISE_TIME_NS ,
  .fallDelay_ns         = COLD_LED_PWM_FALL_DELAY_NS,
  .fallTime_ns          = COLD_LED_PWM_FALL_TIME_NS ,

  .driver_riseDelay_ns  = COLD_LED_PWM_DRIVER_RISE_DELAY_NS,
  .driver_riseTime_ns   = COLD_LED_PWM_DRIVER_RISE_TIME_NS ,
  .driver_fallDelay_ns  = COLD_LED_PWM_DRIVER_FALL_DELAY_NS,
  .driver_fallTime_ns   = COLD_LED_PWM_DRIVER_FALL_TIME_NS ,

  .dutyCycles           = coldLED_MOSFET_dutyCycles ,
  .discreeteLevels      = sizeof(coldLED_MOSFET_dutyCycles) / sizeof(coldLED_MOSFET_dutyCycles[0]),
  .currentDutyCycleIndex= 0u
};

///TODO: calculate heat dissipation and brightness values derived from mosfet values

/* Local SM checks */
static inline bool intensityUpdated()
{
  return (current_white_intensity_index != white_intensity);
}

static inline bool stopRequested()
{
  return false;
}

static inline bool startRequested()
{
  return false;
}

uint8_t coldLedSM_init()
{
  uint8_t retVal = 0;
  /* Calculate mosfet values */
  current_white_intensity_index = 0;
  retVal = init_pulsed_fetControl(&coldLED_MOSFET_specs);
  coldLedState = RUNNING;

  return retVal;
}


uint8_t coldLedSM_run()
{
  uint8_t retVal = 0u;

  bool loop = true;

  while(loop)
  {
    switch(coldLedState)
    {
      case UNINITIALIZED:
        coldLedState = FAULT;
      break;
      
      case RUNNING:
        if(true == stopRequested())
        {
          coldLedState = STOPPED;
        }
        else
        if(true == intensityUpdated())
        {
          update_pulsed_fetControl(&coldLED_MOSFET_specs, (white_intensity % coldLED_MOSFET_specs.discreeteLevels));
          current_white_intensity_index = white_intensity;
          loop = false;
        }
        else
        {
          loop = false;
        }
      break;
      
      case STOPPED:
        if(true == startRequested())
        {
          coldLedState = RUNNING;
        }
        else
        {
          loop = false;
        }
      break;

      case FAULT:
        ///TODO: return error code
        loop = false;
      break;
    }
  }
  return retVal;
}