#ifndef PIN_CONTROL_H
#define PIN_CONTROL_H

#include <stdio.h>

typedef enum pinRole
{
    PIN_UNUSED,
    PIN_ADC,
    PIN_GPIO,
    PIN_PWM,
    PIN_OTHER
};

uint8_t setPinConfiguration();

uint8_t updatePinData();

#endif