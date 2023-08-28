#include "QuadratureEncoderSM.h"

#define GPIO_DIR_INPUT  false
#define GPIO_DIR_OUTPUT true
#define AB_PINS_MASK    0b011
#define C_PIN_MASK      0b100


uint8_t init_QuadratureEncoderSM(QuadratureEncoderSM *encoderSM)
{
    uint8_t retVal = 0u;
    /* Initialize encoder GPIO pins */
    gpio_init(encoderSM->pinA);
    gpio_init(encoderSM->pinB);
    gpio_init(encoderSM->pinC);

    gpio_set_dir(encoderSM->pinA, GPIO_DIR_INPUT);
    gpio_set_dir(encoderSM->pinB, GPIO_DIR_INPUT);
    gpio_set_dir(encoderSM->pinC, GPIO_DIR_INPUT);

    gpio_set_input_hysteresis_enabled(encoderSM->pinA, true);
    gpio_set_input_hysteresis_enabled(encoderSM->pinB, true);
    gpio_set_input_hysteresis_enabled(encoderSM->pinC, true);

    return retVal;
}

uint8_t run_QuadratureEncoderSM(QuadratureEncoderSM *encoderSM)
{
    uint8_t retVal;
    uint8_t abVal;
    bool pinValA;
    bool pinValB;
    bool pinValC;

    pinValA = gpio_get(encoderSM->pinNoA);
    pinValB = gpio_get(encoderSM->pinNoB);
    pinValC = gpio_get(encoderSM->pinNoC);
    abVal = (pinValA << 0) | (pinValB << 1);

    if((encoderSM->oldState & AB_PINS_MASK) != abVal)
    {
        if()
        encoderSM->newState |= abVal;
    }
    
    return retVal;
}