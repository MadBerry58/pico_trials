#ifndef MOSFET_CONTROL_H
#define MOSFET_CONTROL_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"

typedef struct
{
    uint8_t     controlPin;
    uint8_t     sliceNum;
    uint8_t     polarity; /* Allow for both P and N channel PWM control */

    uint8_t     stepNumber;
    uint16_t   *stepPercentages;
    
    uint16_t    riseDelay_ns;
    uint16_t    riseTime_ns;
    uint16_t    fallDelay_ns;
    uint16_t    fallTime_ns;

    uint16_t    minActiveTime_ns;
    uint16_t    minInactiveTime_ns;

    uint16_t    minPinHigh_ns;
    uint16_t    minPinLow_ns;
    uint16_t    maxFrequency_hz;
    pwm_config  config;
} MOSFET_specs;

uint8_t init_mosfetControl(MOSFET_specs *mosfet);

uint8_t update_mosfetControl(MOSFET_specs *mosfet);

#endif
