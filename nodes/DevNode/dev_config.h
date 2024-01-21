#ifndef DEV_CONFIG_H
#define DEV_CONFIG_H

#include "../../../picoOS/picoOS.h"

#define RGB_RING_PIN                        2
#define RGB_RING_PIXEL_NUMBER               16
#define RGB_STRIP_PIN                       3
#define RGB_STRIP_PIXEL_NUMBER              300

#define COLD_LED_PWM_PIN                    4 /* warm LED PWM control pin */
#define COLD_LED_PWM_SLICE_NUM              1
#define COLD_LED_PWM_CHANNEL                0
#define COLD_LED_PWM_POLARITY               true
#define COLD_LED_PWM_RISE_DELAY_NS          5u
#define COLD_LED_PWM_RISE_TIME_NS           14u
#define COLD_LED_PWM_FALL_DELAY_NS          4u
#define COLD_LED_PWM_FALL_TIME_NS           30u
#define COLD_LED_PWM_DRIVER_RISE_DELAY_NS   5u
#define COLD_LED_PWM_DRIVER_RISE_TIME_NS    14u
#define COLD_LED_PWM_DRIVER_FALL_DELAY_NS   4u
#define COLD_LED_PWM_DRIVER_FALL_TIME_NS    30u

#define WARM_LED_PWM_PIN                    5 /* cold LED PWM control pin */
#define WARM_LED_PWM_SLICE_NUM              2
#define WARM_LED_PWM_CHANNEL                0
#define WARM_LED_PWM_POLARITY               true
#define WARM_LED_PWM_RISE_DELAY_NS          5u
#define WARM_LED_PWM_RISE_TIME_NS           14u
#define WARM_LED_PWM_FALL_DELAY_NS          4u
#define WARM_LED_PWM_FALL_TIME_NS           30u
#define WARM_LED_PWM_DRIVER_RISE_DELAY_NS   5u
#define WARM_LED_PWM_DRIVER_RISE_TIME_NS    14u
#define WARM_LED_PWM_DRIVER_FALL_DELAY_NS   4u
#define WARM_LED_PWM_DRIVER_FALL_TIME_NS    30u


///TODO: Add overlapping pins compile time protection

#define ENCODER_AB_PINS             14
#define ENCODER_C_PIN               13
#define ENCODER_STEP_RATE   0 /* 0 - unlimited rate */

#define CYCLE_TIME                  50u /* ms of sleep time between while cycles */

/* Helper functions */
#define MS_TO_US(value) (value * 1000u)

/* Local definitions */
#define BUTTON_PRESSED              true
#define PUSH_BUTTON_DEBOUNCE_MS     100u
#define SWITCH_TIME_MS              3000u
#define SAVE_TO_FAVORITES_TIME_MS   8000u
#define NOTIFICATION_TIME_MS        1000u

#define MULTITAP_TIMEOUT_MS         500u

#define CUSTOMIZATION_TIMEOUT       5000u

/************************************************
 * State machines
 ************************************************/

// /**
//  * @brief 
//  * 
//  */

// /* State machine configurations */
// pushButtonSM_type pushButtonSM_encoder_config = 
// {
//     .pinPull            = true,
//     .buttonPin          = 6u,
//     .debounceTimeC_us   = MS_TO_US(PUSH_BUTTON_DEBOUNCE_MS),
//     .buttonPressed      = &(encoderPushButton_status)
// };

typedef enum 
{
    RGB_control,
    LED_control,

    no_of_Targets
} Targets;

typedef enum
{
    RGB_RUNNING,
    RGB_SETTING,
    RGB_STOPPED
} RGB_State;


typedef struct 
{
    uint8_t  button_time_pressed :  7; /*  7 */
    uint8_t  encoder_position    :  8; /* 15 */
    uint8_t  button_state        :  1; /* 16 */
    uint8_t  white_intensity     :  4; /* 20 */
    uint8_t  white_color         :  4; /* 24 */
    uint8_t  rgb_pattern_index   :  4; /* 28 */
    uint8_t  rgb_intensity       :  4; /* 32 */
    uint8_t  rgb_setting_0       :  4; /* 36 */
    uint8_t  rgb_setting_1       :  4; /* 40 */
    uint8_t  rgb_setting_2       :  4; /* 44 */
    uint64_t reserved            : 20; /* 64 */
}frame0_dev_tx_type;

extern bool     pushButton_updateFlag;
extern bool     encoderPosition_updateFlag;

extern bool     buttonState;
extern uint32_t buttonTimePressed;
extern uint8_t  encoderPosition;


#endif