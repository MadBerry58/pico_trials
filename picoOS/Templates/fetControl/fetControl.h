#ifndef MOSFET_CONTROL_H
#define MOSFET_CONTROL_H

#include "hardware/pwm.h" /* Included for pwm_config */
#include "pico/stdlib.h"

typedef struct
{
    uint8_t     controlPin;
    uint8_t     polarity; /* Allow for both P and N channel PWM control */
    uint8_t     slice_num;
    uint8_t     channel;
    uint32_t    frequency_kHz;
    pwm_config  config;

    /* FET timing values */
    uint16_t    riseDelay_ns;
    uint16_t    riseTime_ns;
    uint16_t    fallDelay_ns;
    uint16_t    fallTime_ns;

    /* Driver overlay timing values */
    uint16_t    driver_riseDelay_ns;
    uint16_t    driver_riseTime_ns;
    uint16_t    driver_fallDelay_ns;
    uint16_t    driver_fallTime_ns;

    /* FET load data */
    uint16_t    max_load;
    uint16_t    power_dissipation;

    uint16_t    currentDutyCycle;
    uint16_t   *dutyCycles;
    uint8_t     discreeteLevels;
    uint8_t     currentDutyCycleIndex;
} Pulsed_FET_specs;

typedef struct
{
    uint8_t     controlPin;
    uint8_t     polarity; /* Allow for both P and N channel PWM control */
    uint8_t     slice_num;
    uint8_t     channel;
    uint16_t    duty_cycle;

    uint16_t    riseDelay_ns;
    uint16_t    riseTime_ns;
    uint16_t    fallDelay_ns;
    uint16_t    fallTime_ns;

    uint16_t    driver_riseDelay_ns;
    uint16_t    driver_riseTime_ns;
    uint16_t    driver_fallDelay_ns;
    uint16_t    driver_fallTime_ns;

    uint16_t    minActiveTime_ns;
    uint16_t    minInactiveTime_ns;

    uint16_t    minPinHigh_ns;
    uint16_t    minPinLow_ns;
    uint16_t    maxFrequency_hz;
    pwm_config  config;

    uint16_t   *dutyCycles;
    uint8_t     discreeteLevels;
} Voltage_FET_specs;

uint8_t init_voltage_fetControl     (Voltage_FET_specs *fet);
uint8_t update_voltage_fetControl   (Voltage_FET_specs *fet);

uint8_t init_pulsed_fetControl      (Pulsed_FET_specs  *fet);
uint8_t update_pulsed_fetControl    (Pulsed_FET_specs  *fet, uint8_t newIndex);

#endif
