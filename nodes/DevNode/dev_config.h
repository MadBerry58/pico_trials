#ifndef DEV_CONFIG_H
#define DEV_CONFIG_H

#include "../../../picoOS/picoOS.h"

#define RGB_RING_PIN                2
#define RGB_RING_PIXEL_NUMBER       16
#define RGB_STRIP_PIN               3
#define RGB_STRIP_PIXEL_NUMBER      300

#define COLD_LED_PWM_PIN            4 /* warm LED PWM control pin */
#define COLD_LED_PWM_

#define WARM_LED_PWM_PIN            5 /* cold LED PWM control pin */
#define WARM_LED_PWM_

#define ENCODER_AB_PINS             16
#define ENCODER_C_PIN               18 /* GPIO18 */

#define CYCLE_TIME                  50u /* ms of sleep time between while cycles */

#define SWITCH_TIME                 3000u 
#define CUSTOMIZE_TIME              1000u

/* Helper functions */
#define MS_TO_US(value) (value * 1000u)

/* Local definitions */
#define BUTTON_PRESSED              true
#define PUSH_BUTTON_DEBOUNCE_MS     100u
#define SWITCH_TIME_MS              1000u
#define CUSTOMIZE_PATTERN_TIME_MS   3000u
#define NOTIFICATION_TIME_MS        1000u

#define MULTITAP_TIMEOUT_MS         500u

#define CUSTOMIZATION_TIMEOUT       5000u

/************************************************
 * State machines
 ************************************************/



/**
 * @brief 
 * 
 */
// quadrature_encoder_sm quadratureSM = {
//     .smID             = 0,
//     .abPin            = ENCODER_AB_PINS,
//     .buttonPin        = ENCODER_C_PIN,
//     .buttonOutput     = &buttonState,
//     .rotationOutput   = &encoderPosition,
//     .loopControl      = false,
//     .prevButton       = 0,
//     .prevRotation     = 0,
//     .notificationFlag = SM_QUADRATURE_N_NONE,
//     .sm_state         = SM_QUADRATURE_UNINIT,
//     .sm_request       = SM_QUADRATURE_R_NONE
// };

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

#endif