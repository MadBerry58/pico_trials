#include "pwm.h"
#include "pwmTemplates.h"

uint8_t pwm_init()
{
    uint8_t retVal = 0u;

    gpio_set_function(pinNo, GPIO_FUNC_PWM);

    return retVal;
}

uint8_t pwm_set(/* pwn config, external variable */)
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t pwm_updateData()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t pwm_generateTemplateConfig(uint8_t pinNo, pwmTemplate_t template)
{
    uint8_t retVal = 0u;
    
    uint slice_num = pwm_gpio_to_slice_num(pinNo);
    pwm_set_wrap(slice_num, template.wrap);
    
    return retVal;
}