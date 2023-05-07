#include "adc.h"

#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/dma.h"

#define ADC_FIFO_SAMPLE_BUFFER 12u
#define ROUND_ROBIN_TEMP_PIN
#define ROUND_ROBIN_VSYS3_PIN
#define ROUND_ROBIN_GPIO29_PIN
#define ROUND_ROBIN_TEMP_PIN
#define ROUND_ROBIN_TEMP_PIN

uint16_t sysTemp;

uint16_t adc_samples[ADC_FIFO_SAMPLE_BUFFER];

/**
 * @brief Simplified version: all required pins are sampled in round robin mode. each sample takes 96cycles at 48MHz, ~2us
 * 
 * @param adcConfig 
 * @return uint8_t 
 */
uint8_t adc_init(adcConfig_t adcConfig)
{
    adc_set_temp_sensor_enabled();
    adc_set_round_robin(0b00011000)
    /* Set the FIFO/DMA */
    /* Set FIFO/DMA interrupt handler */
}