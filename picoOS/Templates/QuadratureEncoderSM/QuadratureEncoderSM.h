#ifndef QUADRATURE_ENCODER_SM
#define QUADRATURE_ENCODER_SM

#include <stdio.h>
#include "pico/stdlib.h"

typedef struct QuadratureEncoderSM
{
    uint8_t oldState;

    uint8_t pinNoA;
    uint8_t pinNoB;
    uint8_t pinNoC;

    int delta;
    int position;
};


#endif