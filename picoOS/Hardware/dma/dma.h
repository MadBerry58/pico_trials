#ifndef DMA_H
#define DMA_H

#include <stdio.h>
#include "dma_configs.h"

enum ADC_pins
{
    ADC_Pin0,
    ADC_Pin1,
    ADC_Pin2,
    ADC_TempSensor,
    ADC_PinNo
};

uint8_t init_DMA(void);

uint8_t run_DMA(void);

#endif