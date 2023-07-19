#include "EncoderSM.h"
#include "../../../picoOS/picoOS.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/rtc.h"

/* Temp PWM code */
volatile uint       slice_num           = 0u;
/*  */

#define	LEDPIN      25u
#define	A_Pin 	    18u

#ifdef PIO_QUADRATURE_ENCODER
#define	B_Pin       A_Pin + 1u
PIO quadrature_pio = pio0;
const uint quadrature_sm = 0;
int new_value, old_value = 0;
#else
#define	B_Pin       19u
#define A_Mask      0b001
#define B_Mask      0b010
#define AB_Mask     0b011
#define C_Mask      0b100
uint8_t prevState = 0b000;
uint8_t currState = 0b000;
uint8_t tempState = 0b000;
volatile uint       slice_num           = 0u;

#endif

#define CW_Rotation 1
#define CCW_Rotation -1

#define	C_Pin       20u
//TODO: create GPIO configuration

#define debounceTimeMS 10u

uint8_t delta = 0u;

enum SM_state_t
{
     UNINITIALIZED
    ,INITIALIZED
    ,IDLE
    ,PRESSED
    ,RELEASED
    ,CW
    ,CCW
    #ifndef PIO_QUADRATURE_ENCODER
    ,CW_DEBOUNCE
    ,CCW_DEBOUNCE
    #endif
    ,PRESSED_DEBOUNCE
    ,RELEASED_DEBOUNCE
    
} smState;

volatile uint8_t    ledLevel            = 0u;
volatile uint8_t    ledLevelTemp        = 0u;
volatile uint16_t   ledOutput           = 0u;

int EncoderSM_init(void)
{
    uint8_t retVal = 0u;

    /* Temp PWM code */
    gpio_set_dir(LEDPIN,    GPIO_OUT);
    gpio_set_function(LEDPIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(LEDPIN);
    pwm_clear_irq(slice_num);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);
    /*  */

    gpio_set_dir(C_Pin,     GPIO_IN);
    #ifdef PIO_QUADRATURE_ENCODER
    /* Create configuration variable chain */
    uint offset = pio_add_program(quadrature_pio, &quadrature_encoder_program);
    quadrature_encoder_program_init(quadrature_pio, quadrature_sm, offset, A_Pin, 0);
    #else
    /* Create bitmasks used for coded gpio encoder */

    /* Create AB GPIO bindings */

    #endif

    return retVal;
}

void checkEncoder(void)
{

    #ifdef PIO_QUADRATURE_ENCODER
    new_value = quadrature_encoder_get_count(quadrature_pio, quadrature_sm);
    delta = new_value - old_value;
    old_value = new_value;
    #else
    /* Add gpio bit checking sub-state machine */
    
    ///TODO: Add configuration for pulse vs toggle encoders
    ///TODO: Add interrupt vs poll coinfiguration
    
    /* Poll_Toggle implementation */
    currState = (gpio_get(A_Pin) << 0u) + (gpio_get(B_Pin) << 1u);
    switch(currState ^ prevState)
    {
        case A_Mask:
        case B_Mask:
            tempState = (currState ^ prevState); 
        case AB_Mask:
            delta   +=(CCW_Rotation) * (tempState == A_Mask) 
                    + ( CW_Rotation) * (tempState == B_Mask);
            prevState = currState;

    }

    /* IRQ_Toggle  implementation */

    /* IRQ_Pulse   implementation */
    gpio_set_irq_enabled_with_callback(A_Pin, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(B_Pin, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(C_Pin, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    #endif

}

int EncoderSM_run(uint *response)
{
    checkEncoder();
    ledOutput = ledLevel * ledLevel;
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, ledOutput);
}