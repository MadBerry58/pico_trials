#ifndef ADC_H
#define ADC_H

typedef struct adcConfig_t 
{
    bool useChan0;
    bool useChan1;
    bool useChan2;
    bool freeRun;
    /**
     * @brief sampling rate is 96 cycles per sample
     * 
     */
} adcConfig;

#endif