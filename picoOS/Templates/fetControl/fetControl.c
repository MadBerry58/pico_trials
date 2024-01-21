#include "fetControl.h" 
#include "hardware/clocks.h"

#define NANOSECONDS_IN_SECOND 1000000000lu

uint8_t init_pulsed_fetControl      (Pulsed_FET_specs  *fet)
{
    uint8_t retVal = 0u;

    /* Initialize pwm functionality */
    fet->config        = pwm_get_default_config ();
    fet->slice_num     = pwm_gpio_to_slice_num  (fet->controlPin);
    fet->channel       = pwm_gpio_to_channel    (fet->controlPin);

    /* Calculate FET pulse timings */
     /* Calculate power dissipation limit - */
      /* Calculate ON power dissipation */
      /* Calculate temperature stabilization time */
      /* Calculate transient switching thermal resistance */
       /* In order to reduce thermal cycling, do not allow a high thermal difference */

    /* Initialize PWM hardware */
    gpio_set_function(fet->controlPin, GPIO_FUNC_PWM);
    pwm_config_set_clkdiv(&(fet->config), 1u/* (float)(SYS_CLK_KHZ/fet->frequency_kHz) */);
    pwm_init(fet->slice_num, &(fet->config), true);

    return retVal;
}

uint8_t update_pulsed_fetControl    (Pulsed_FET_specs  *fet, uint8_t newIndex)
{
    uint8_t retVal = 0u;

    fet->currentDutyCycleIndex = newIndex;
    fet->currentDutyCycle = fet->dutyCycles[fet->currentDutyCycleIndex];
    pwm_set_gpio_level(
            fet->controlPin,
            fet->currentDutyCycle
        );

    return retVal;
}


uint8_t init_voltage_fetControl     (Voltage_FET_specs *fet)
{
    return 0;
}
uint8_t update_voltage_fetControl   (Voltage_FET_specs *fet)
{
    return 0;
}