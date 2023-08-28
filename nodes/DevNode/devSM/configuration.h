#ifndef DEV_CONFIG_H
#define DEV_CONFIG_H

#include "../../../picoOS/picoOS.h"

#define ENCODER_AB_PINS     16
 /* GPIO16, 17 */
#define ENCODER_C_PIN       18 /* GPIO18 */
#define WS2812_PIN          2
#define LED_PIN             3 /* LED PWM control pin */
#define PIXEL_NUMBER        16
#define CYCLE_TIME          50u /* ms of sleep time between while cycles */

#define SWITCH_TIME         3000u 
#define CUSTOMIZE_TIME      1000u

#define Button_Pressed      true
#define Button_Released     false

uint32_t rgbPatterns[][PIXEL_NUMBER] = {
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000
    },
    {
        0xaa000000,
        0xaa110000,
        0x99220000,
        0x99331100,
        0x88442200,
        0x88553300,
        0x77664400,
        0x77775500,
        0x66886600,
        0x66997700,
        0x44aa8800,
        0x33bb9900,
        0x22ccaa00,
        0x22ddbb00,
        0x11eecc00,
        0x11ffdd00
    },
    {
        0x00000000,
        0x11111100,
        0x22222200,
        0x33333300,
        0x44444400,
        0x55555500,
        0x66666600,
        0x77777700,
        0x88888800,
        0x99999900,
        0xaaaaaa00,
        0xbbbbbb00,
        0xcccccc00,
        0xdddddd00,
        0xeeeeee00,
        0xffffff00
    },
    {
        0xffffff00,
        0xeeeeee00,
        0xdddddd00,
        0xcccccc00,
        0xbbbbbb00,
        0xaaaaaa00,
        0x99999900,
        0x88888800,
        0x77777700,
        0x66666600,
        0x55555500,
        0x44444400,
        0x33333300,
        0x22222200,
        0x11111100,
        0x00000000
    },
    {
        0x11ffdd00,
        0x22eecc00,
        0x44ccaa00,
        0xee220000,
        0xbb553300,
        0x55bb9900,
        0x99775500,
        0xaa664400,
        0x88886600,
        0x77997700,
        0x66aa8800,
        0xcc442200,
        0xdd331100,
        0x33ddbb00,
        0xff110000,
        0xff000000
    }
};


ws2812_sm_pattern patterns[] = 
{
    {/* blank pattern */
        .patternSize        = PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns)[0])
    },
    {
        .patternSize        = PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns[1]))
    },
    {
        .patternSize        = PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns[2]))
    },
    {
        .patternSize        = PIXEL_NUMBER,
        .patternNumber      = 4,
        .refreshRate        = 1000,
        .patternList        = (uint32_t**)(&(rgbPatterns[1]))
    }
};
const uint8_t patternNumber = sizeof(patterns) / sizeof(patterns[0]);


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

ws2812_sm ws2812SM = {
    .smID               = 1,
    .pin                = WS2812_PIN,
    .updateFlag         = false,
    .loopControl        = false,
    .patternLocation    = (&(patterns[0])),
    .notificationFlag   = SM_WS2812_N_NONE,
    .sm_state           = SM_WS2812_UNINIT,
    .sm_request         = SM_WS2812_R_NONE
};
static bool buttonState;
static bool prevButtonState;
static uint32_t msPressed;
static uint32_t prevTime;

/* Quadrature encoder  */
static uint8_t encoderPosition;
static uint8_t encoderPosition_old;
quadrature_encoder_sm quadratureSM = {
    .smID             = 0,
    .abPin            = ENCODER_AB_PINS,
    .buttonPin        = ENCODER_C_PIN,
    .buttonOutput     = &buttonState,
    .rotationOutput   = &encoderPosition,
    .loopControl      = false,
    .prevButton       = 0,
    .prevRotation     = 0,
    .notificationFlag = SM_QUADRATURE_N_NONE,
    .sm_state         = SM_QUADRATURE_UNINIT,
    .sm_request       = SM_QUADRATURE_R_NONE
};


Task_t devSM_tasks[] = {
    {
        .taskID         = 1u,
        .taskFunction   = NULL,
        .priority       = T_Prio_MODERATE,
        .cycleTime      = 5u,
        .nextTrigger    = 0u
    },
    {
        .taskID         = 1u,
        .taskFunction   = NULL,
        .priority       = T_Prio_MODERATE,
        .cycleTime      = 5u,
        .nextTrigger    = 0u
    }
};

static Targets target;

#endif