#ifndef LIGHTSWITCH_CONFIG_H
#define LIGHTSWITCH_CONFIG_H

#include "../../picoOS/picoOS.h"

#define RGB_RING_PIN                2
#define RGB_RING_PIXEL_NUMBER       16

#define ENCODER_AB_PINS             16
#define ENCODER_C_PIN               18 /* GPIO18 */
#define ENCODER_STEP_RATE           0 /* 0 - unlimited rate */

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

#endif