#ifndef DEV_CONFIG_H
#define DEV_CONFIG_H

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
 * CAN bus
 ************************************************/
#include "../../picoOS/Comm/CAN/CAN_SM_APIs.h"

#define BROADCAST_FRAME_ID                  167u
#define BROADCAST_FRAME_DLC                 4u
#define BROADCAST_FRAME_SIGNAL_NO           4u

#define LIGHT_SWITCH_FRAME_ID               170u 
#define LIGHT_SWITCH_FRAME_DLC              1u 
#define LIGHT_SWITCH_FRAME_SIGNAL_NO        1u 

#define LIGHT_CONTROLLER_FRAME_ID           183u
#define LIGHT_CONTROLLER_FRAME_DLC          1
#define LIGHT_CONTROLLER_FRAME_SIGNAL_NO    1

MCP2515_instance mainBus = 
{
    .RX_PIN         = 16u,
    .CS_PIN         = 17u,
    .SCK_PIN        = 18u,
    .TX_PIN         = 19u,
    .INT_PIN        = 20u,
    .SPI_CLOCK      = (8 * 1000 * 1000), /* 8 Mhz*/

    .rxStatus       = 0u,
    .icStatus       = 0u
};

CanIf_frame CanIf_RxFrames[] = 
{
    { // Broadcast frame
        {
            .can_id     = BROADCAST_FRAME_ID,
            .can_dlc    = BROADCAST_FRAME_DLC,
            .data       = {0u}
        },
        .frameRxCallback    = NULL,
        .IPC_variables      = NULL,
        .frameSignalNo      = BROADCAST_FRAME_SIGNAL_NO,
        .frameUpdated       = false
    },
    { // LightSwitch frame
        {
            .can_id     = LIGHT_SWITCH_FRAME_ID,
            .can_dlc    = LIGHT_SWITCH_FRAME_DLC,
            .data       = {0u}
        },
        .frameRxCallback    = NULL,
        .IPC_variables      = NULL,
        .frameSignalNo      = LIGHT_SWITCH_FRAME_SIGNAL_NO,
        .frameUpdated       = false
    },
    { // LightController frame
        {
            .can_id     = LIGHT_CONTROLLER_FRAME_ID,
            .can_dlc    = LIGHT_CONTROLLER_FRAME_DLC,
            .data       = {0u}
        },
        .frameRxCallback    = NULL,
        .IPC_variables      = NULL,
        .frameSignalNo      = LIGHT_SWITCH_FRAME_SIGNAL_NO,
        .frameUpdated       = false
    }
};

canIf_frame CanIf_TxFrames[] = 
{
    { // Broadcast frame
        {
            .can_id     = BROADCAST_FRAME_ID,
            .can_dlc    = BROADCAST_FRAME_DLC,
            .data       =   {
                                29u,
                                23u,
                                19u,
                                17u
                            }
        },
        .frameRxCallback    = NULL,
        .IPC_variables      = NULL,
        .frameSignalNo      = BROADCAST_FRAME_SIGNAL_NO,
        .frameUpdated       = false
    }
};

CanIf_t mainCanIf = 
{
    .canBusCfg = mainBus,

    .txIfFrames     = CanIf_TxFrames,
    .txIfFrame_no   = (sizeof(CanIf_RxFrames) / sizeof(canIf_frame)),

    .rxIfFrames     = CanIf_RxFrames,
    .rxIfFrame_no   = (sizeof(CanIf_RxFrames) / sizeof(canIf_frame))
}

#endif