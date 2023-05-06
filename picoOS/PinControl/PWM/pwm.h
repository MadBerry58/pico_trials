#ifndef PWM_H
#define PWM_H


uint8_t pwm_init();

uint8_t pwm_set(/* pwn config, external variable */);
uint8_t pwm_updateData();

uint8_t pwm_generateTemplateConfig(uint8_t pinNo, pwmTemplate_t template);

#endif