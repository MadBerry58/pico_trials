#include "dma.h"

#ifdef ADC_PIN0_ACTIVE
    #ifndef ADC_PIN0_BUFFER_SIZE
    #define ADC_PIN0_BUFFER_SIZE 5u
    #endif
uint16_t adcPin0_Buffer[ADC_PIN0_BUFFER_SIZE];
#endif

#ifdef ADC_PIN1_ACTIVE
    #ifndef ADC_PIN1_BUFFER_SIZE
    #define ADC_PIN1_BUFFER_SIZE 5u
    #endif
uint16_t adcPin1_Buffer[ADC_PIN1_BUFFER_SIZE];
#endif

#ifdef ADC_PIN2_ACTIVE
    #ifndef ADC_PIN2_BUFFER_SIZE
    #define ADC_PIN2_BUFFER_SIZE 5u
    #endif
uint16_t adcPin2_Buffer[ADC_PIN2_BUFFER_SIZE];
#endif

/* ADC round robin mask */
uint8_t adcPinMask = 
    #ifdef ADC_PIN0_ACTIVE
    (1 << ADC_Pin0) |
    #endif

    #ifdef ADC_PIN1_ACTIVE
    (1 << ADC_Pin1) |
    #endif

    #ifdef ADC_PIN2_ACTIVE
    (1 << ADC_Pin2) |
    #endif

    (1 << ADC_TempSensor)
;

uint8_t freeDMAchannels = 8u;

static uint8_t OS_DMA_controlBlock();

uint8_t init_DMA(void)
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t run_DMA(void)
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t runDMA_transferLoop()
{
    uint8_t retVal = 0u;

    return retVal;
}

/**
 * @brief OS control->data DMA pair
 * 
 * @return uint8_t 
 */
uint8_t OS_DMA_controlBlock()
{
    uint8_t retVal = 0u;

    return retVal;
}

///NOTE: by using different DMA channels with different DREQ triggers, the control block chain can be triggered to transfer the data