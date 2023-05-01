#include "EncoderSM.h"

#define A_Pin_SetMask     0b001
#define A_Pin_ResetMask   0b110

#define B_Pin_SetMask     0b010
#define B_Pin_ResetMask   0b101

#define C_Pin_SetMask     0b100
#define C_Pin_ResetMask   0b011

#define	LEDPIN      25u
#define	A_Pin 	    20u
#define	C_Pin       19u
#define	B_Pin       18u

#define debounceTimeMS 10u

enum SM_state_t
{
    UNINITIALIZED,
    INITIALIZED,
    IDLE,
    PRESSED_DEBOUNCE,
    PRESSED,
    RELEASED_DEBOUNCE,
    RELEASED,
    CW_DEBOUNCE,
    CW_COMPLETE,
    CCW_DEBOUNCE,
    CCW_COMPLETE

} smState;

enum EncoderState_t
{
    NONE,
    A,
    B,
    C,
    AB
};
volatile uint       slice_num           = 0u;
volatile uint       pinStatePrev        = 0b000;
volatile uint       pinStateCurr        = 0b000;
volatile uint       encoderState        = NONE;
volatile uint       prevEncoderState    = NONE;
volatile bool       debounceStarted     = false;
volatile bool       debounceExpired     = false;

volatile uint8_t    ledLevel            = 0u;
volatile uint8_t    ledLevelTemp        = 0u;
volatile uint16_t   ledOutput           = 0u;

/**
 * @brief 
 * 
 * @param gpio 
 * @param events 
 *
 * Right:  A_Low -> B_Low -> A_High -> B_High
 * Left:   B_Low -> A_Low -> B_High -> A_High
 * Center: C_Low -> C_High
 *  
 */

int64_t debounceStart(alarm_id_t id, void *user_data)
{
    debounceExpired = false;
    // printf("Debounce Expired\n");
    return 0ul;
}

int EncoderSM_init(void)
{
	gpio_init(A_Pin);
	gpio_init(B_Pin);
	gpio_init(C_Pin);
	gpio_init(LEDPIN);

	gpio_pull_up(A_Pin);
	gpio_pull_up(B_Pin);
	gpio_pull_up(C_Pin);

    gpio_set_dir(LEDPIN,    GPIO_OUT);
    gpio_set_dir(A_Pin,     GPIO_IN);
    gpio_set_dir(B_Pin,     GPIO_IN);
    gpio_set_dir(C_Pin,     GPIO_IN);

	gpio_set_function(LEDPIN, GPIO_FUNC_PWM);
	// Find out which PWM slice is connected to LEDPIN
	slice_num = pwm_gpio_to_slice_num(LEDPIN);
    pwm_clear_irq(slice_num);
    // Get some sensible defaults for the slice configuration. By default, the
    // counter is allowed to wrap over its maximum range (0 to 2**16-1)
    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 4.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);
    smState = INITIALIZED;

    return 0u;
}

void checkPins(void)
{
    uint retVal = 0u;
    pinStateCurr = (gpio_get(A_Pin) << 0u) + (gpio_get(B_Pin) << 1u) + (gpio_get(C_Pin) << 2u);

    switch(pinStateCurr)
    {
        case 0b011:
            /* Center Triggered */
            encoderState = C;
            break;

        case 0b100:
            /* Stage 2 rotation */
            encoderState = AB;
            break;

        case 0b101:
            /* Pin B triggered */
            encoderState = B;
            break;

        case 0b110:
            /* Pin A triggered */
            encoderState = A;
            break;

        case 0b001:
        case 0b010:
        case 0b111:
            /* No pin triggered */
            encoderState = NONE;
            break;
    }   

    pinStatePrev = pinStateCurr;
    prevEncoderState = encoderState;
}

int EncoderSM_run(uint *response)
{
    *response = 0;
    int currentPin = 0;
    int retVal = -1;
    checkPins();
    // printf("ExecutingSM\n");
    switch(smState)
    {
        case UNINITIALIZED:
            /* Return intial -1 value */
        break;

        case INITIALIZED:
            /* SM initialized, go to idle */
            smState = IDLE;
        break;
        
        case IDLE:
            // printf("ExecutingSM_IDLE\n");
            switch(encoderState)
            {
                case C:
                smState = PRESSED_DEBOUNCE;
                break;

                case A:
                smState = CW_DEBOUNCE;
                break;

                case B:
                smState = CCW_DEBOUNCE;
                break;

                case NONE:
                smState = IDLE;
                break;
            }
        break;
        
        case PRESSED_DEBOUNCE:
            printf("Debouncing Press\n");
            if(C == pinStateCurr)
            {
                if(!debounceStarted)
                {
                    add_alarm_in_ms(debounceTimeMS, debounceStart, NULL, true);
                    debounceStarted = true;
                    debounceExpired = false;
                    smState = PRESSED_DEBOUNCE;
                }
                else
                if(debounceStarted && !debounceExpired)
                {
                    debounceStarted = false;
                    ledLevelTemp = ledLevel;
                    smState = PRESSED;
                }
                else
                {
                    debounceStarted = false;
                    smState = IDLE;
                }
            }
            else
            {
                debounceStarted = false;
                smState = IDLE;
            }
        break;
        
        case PRESSED:
            printf("Button Pressed\n");
            if(C == pinStateCurr)
            {
                ledLevel = 255u;
                smState = PRESSED;
            }
            else
            {
                smState = RELEASED_DEBOUNCE;
            }
        break;
        
        case RELEASED_DEBOUNCE:
            if(C != pinStateCurr)
            {
                if(!debounceStarted)
                {
                    add_alarm_in_ms(debounceTimeMS, debounceStart, NULL, true);
                    debounceStarted = true;
                    debounceExpired = false;
                    smState = PRESSED_DEBOUNCE;
                }
                else
                if(debounceStarted && !debounceExpired)
                {
                    debounceStarted = false;
                    smState = IDLE;
                }
                else
                {
                    debounceStarted = false;
                    smState = PRESSED;
                }
            }
            else
            {
                debounceStarted = false;
                smState = PRESSED;
            }
        break;
        
        case RELEASED:
            printf("Center released");
            *response = 1;
            ledLevel = ledLevelTemp;
            smState = IDLE;
        break;
        
        case CW_DEBOUNCE:
            if(!debounceStarted)
            {
                add_alarm_in_ms(debounceTimeMS, debounceStart, NULL, true);
                debounceStarted = true;
                debounceExpired = false;
                smState = CW_DEBOUNCE;
            }
            else
            if(debounceStarted && !debounceExpired && (AB == encoderState))
            {
                debounceStarted = false;
                smState = CW_COMPLETE;
            }
            else
            {
                debounceStarted = false;
                smState = IDLE;
            }
        break;

        case CW_COMPLETE:
            ledLevel ++;
            printf("CW rotation %u \n", ledLevel);
            *response = 2;
            smState = IDLE;
        break;
    
        case CCW_DEBOUNCE:
            if(!debounceStarted)
            {
                add_alarm_in_ms(debounceTimeMS, debounceStart, NULL, true);
                debounceStarted = true;
                debounceExpired = false;
                smState = CCW_DEBOUNCE;
            }
            else
            if(debounceStarted && !debounceExpired && (AB == encoderState))
            {
                debounceStarted = false;
                smState = CCW_COMPLETE;
            }
            else
            {
                debounceStarted = false;
                smState = IDLE;
            }
        break;

        case CCW_COMPLETE:
            ledLevel --;
            printf("CCW rotation %u \n", ledLevel);
            *response = 3;
            smState = IDLE;
        break;

        default:
        break;
    }
    ledOutput = ledLevel * ledLevel;
    pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, ledOutput);
}