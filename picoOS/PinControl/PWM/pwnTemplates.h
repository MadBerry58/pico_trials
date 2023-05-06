#ifndef PWN_TEMPLATES_H
#define PWN_TEMPLATES_H

#include <stdio.h>

typedef enum chanB_role_t
{
    PWM_NOT_USED,
    PWM_OUTPUT,
    PWM_INPUT
};


struct pwmTemplate_t
{
    chanB_role_t    chanB_role;
    uint8_t         wrap;
    uint16_t        chanA_minDutyCycle;
    uint16_t        chanA_maxDutyCycle;
    uint16_t        chanB_minDutyCycle;
    uint16_t        chanB_maxDutyCycle;
};

pwmTemplate_t pwm_mosfet = 
{
    .chanB_role = PWM_NOT_USED,
    .wrap = 16u,
    .chanA_minDutyCycle = 517u,  /* random placeholder value */
    .chanA_maxDutyCycle = 4177u, /* random placeholder value */
    .chanB_minDutyCycle = 0u,
    .chanB_maxDutyCycle = 0u
};

pwmTemplate_t pwm_fan = 
{
    .chanB_role = PWM_INPUT,
    .wrap = 256u,
    .chanA_minDutyCycle = 78u,  /* random placeholder value */
    .chanA_maxDutyCycle = 63211u, /* random placeholder value */
    .chanB_minDutyCycle = 78u,
    .chanB_maxDutyCycle = 63211u
};

#endif