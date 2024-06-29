#include "servoControl.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define KHZ         1000u
#define SECOND_US   1000000u

uint8_t init_servo  (servoObject *servo)
{
    uint8_t  retVal         = 0;
    uint16_t timeDelta      = 0;

    servo->pwmSliceNo       = pwm_gpio_to_slice_num (servo->pin);
    servo->pwmSliceChannel  = pwm_gpio_to_channel   (servo->pin);

    if(0 == servo->controlFrequencyHz)
    {
        if(0 != servo->controlPeriod_uS)
        {
            servo->controlFrequencyHz = SECOND_US / servo->controlPeriod_uS;
        }
        else
        {
            printf("Servo control frequency/period not provided\n");
            retVal = 1;
        }
    }
    else if(0 == servo->controlPeriod_uS)
    {
        if(0 != servo->controlFrequencyHz)
        {
            servo->controlPeriod_uS = SECOND_US / servo->controlFrequencyHz;
        }
        else
        {
            printf("Servo control frequency/period not provided\n");
            retVal = 1;
        }
    }

    servo->divisor = ((SYS_CLK_KHZ * KHZ) / servo->controlFrequencyHz);

    if(
        (0 < servo->maxPulse_uS) &&
        (0 < servo->minPulse_uS) &&
        (0 < servo->angleRange ) &&
        (servo->maxPulse_uS > servo->minPulse_uS)
    )
    {
        /* Calculate pulse duration per angle within the control delta*/
        servo->timePerAngle_uS = ((servo->maxPulse_uS - servo->minPulse_uS) / servo->angleRange);

        /* Calculate number of angle durations in the entire period*/
        servo->pwmWrap = servo->controlPeriod_uS / servo->timePerAngle_uS;
        
        gpio_set_function (servo->pin, GPIO_FUNC_PWM);
        pwm_set_clkdiv    (servo->pwmSliceNo, servo->divisor);
        pwm_set_wrap      (servo->pwmSliceNo, servo->pwmWrap);
        pwm_set_gpio_level(servo->pin, servo->minPulse_uS);
        pwm_set_enabled   (servo->pwmSliceNo, true);
        
        servo->pwmRunning = true;
    }
    else
    {
        printf("Servo control pulse range not provided\n");
        retVal = 1;
    }


    return retVal;
}

uint8_t set_servo   (servoObject *servo, uint8_t angle)
{
    uint8_t retVal = 0;

    pwm_set_gpio_level(servo->pin, servo->minPulse_uS + (angle * servo->timePerAngle_uS));

    return retVal;
}

uint8_t deinit_servo(servoObject *servo)
{
    uint8_t retVal = 0;

    pwm_set_enabled   (servo->pwmSliceNo, false);

    return retVal;
}