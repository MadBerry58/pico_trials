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

typedef struct pinConfiguration
{
    pinRole pin1  = PIN_UNUSED;
    pinRole pin2  = PIN_UNUSED;
    pinRole pin3  = PIN_UNUSED;
    pinRole pin4  = PIN_UNUSED;
    pinRole pin5  = PIN_UNUSED;
    pinRole pin6  = PIN_UNUSED;
    pinRole pin7  = PIN_UNUSED;
    pinRole pin8  = PIN_UNUSED;
    pinRole pin9  = PIN_UNUSED;
    pinRole pin10 = PIN_UNUSED;
    pinRole pin11 = PIN_UNUSED;
    pinRole pin12 = PIN_UNUSED;
    pinRole pin12 = PIN_UNUSED;
    pinRole pin13 = PIN_UNUSED;
    pinRole pin14 = PIN_UNUSED;
    pinRole pin15 = PIN_UNUSED;
    pinRole pin16 = PIN_UNUSED;
    pinRole pin17 = PIN_UNUSED;
    pinRole pin18 = PIN_UNUSED;
    pinRole pin19 = PIN_UNUSED;
    pinRole pin20 = PIN_UNUSED;
    pinRole pin21 = PIN_UNUSED;
    pinRole pin22 = PIN_UNUSED;
    pinRole pin23 = PIN_UNUSED;
    pinRole pin24 = PIN_UNUSED;
    pinRole pin25 = PIN_UNUSED;
    pinRole pin26 = PIN_UNUSED;
    pinRole pin27 = PIN_UNUSED;
    pinRole pin28 = PIN_UNUSED;
    pinRole pin29 = PIN_UNUSED;
    pinRole pin31 = PIN_UNUSED;
    pinRole pin32 = PIN_UNUSED;
    pinRole pin33 = PIN_UNUSED;
    pinRole pin34 = PIN_UNUSED;
    pinRole pin35 = PIN_UNUSED;
    pinRole pin36 = PIN_UNUSED;
    pinRole pin37 = PIN_UNUSED;
    pinRole pin38 = PIN_UNUSED;
    pinRole pin39 = PIN_UNUSED;
};
uint8_t setPinConfiguration();

uint8_t updatePinData();

#endif