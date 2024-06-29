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


/* Externally used IPC values */
// extern uint8_t   Rxframe_123_var0;
// extern uint8_t   Rxframe_123_var1;
// extern uint8_t   Rxframe_123_var2;
// extern uint16_t  Rxframe_123_var3;
// extern uint16_t  Rxframe_123_var4;
 
// extern uint8_t   Rxframe_456_var0;
// extern uint8_t   Rxframe_456_var1;
// extern uint8_t   Rxframe_456_var2;
 
// extern uint8_t   Rxframe_789_var0;
// extern uint16_t  Rxframe_789_var1;
// extern uint8_t   Rxframe_789_var2;
// extern uint16_t  Rxframe_789_var3;
// extern uint32_t  Rxframe_789_var4;
// extern uint32_t  Rxframe_789_var5;
// extern uint16_t  Rxframe_789_var6;

// can_frame RxBuffer;

/* Rx Frame callbacks */
// void    Cbk_RxFrame_123             (void);

// void    (*FrameCallbacks[1])        (void);
// static uint8_t frameCallbackIndex          = 0u;
// const   
// uint8_t frameCallbacksNo            = 1u;

// /* Rx Signal callbacks */
// void    Cbk_RxSignal_123_var3       (void);
// void    Cbk_RxSignal_456_var0       (void);
// void    Cbk_RxSignal_456_var1       (void);
// void    Cbk_RxSignal_789_var2       (void);
// void    Cbk_RxSignal_789_var6       (void);
// const   
// void    (*SignalCallbacks[5])       (void);
// static uint8_t signalCallbackIndex         = 0u;

// /* CanIf Rx frame declarations */
// uint32_t frameIDlist[] = {
//     0x123,
//     0x456,
//     0x789,
// };

// Rxframe_IPC Frame123_IPC[] = {
//     {
//         .IPC_Variable   = &(Rxframe_123_var0),
//         .bitSize        = 4,
//         .type           = UINT8,
//         .signalCallback = Cbk_RxSignal_123_var3,  
//     },
//     {
//         .IPC_Variable   = &(Rxframe_123_var1),  
//         .bitSize        = 5, 
//         .type           = UINT8 , 
//         .signalCallback = NULL
//     },
//     {
//         .IPC_Variable   = &(Rxframe_123_var2),  
//         .bitSize        = 3, 
//         .type           = UINT8 , 
//         .signalCallback = NULL
//     },
//     {
//         .IPC_Variable   = &(Rxframe_123_var3),  
//         .bitSize        = 9, 
//         .type           = UINT16, 
//         .signalCallback = NULL
//     },
//     {
//         .IPC_Variable   = &(Rxframe_123_var4), 
//         .bitSize        = 11, 
//         .type           = UINT16, 
//         .signalCallback = NULL} 
// };
// const uint8_t Frame123_IPC_byteSize = 4u; 

// Rxframe_IPC Frame456_IPC[] = {
//     {
//         .IPC_Variable   = &(Rxframe_456_var0),
//         .bitSize        =  3, 
//         .type           = UINT8 , 
//         .signalCallback = Cbk_RxSignal_456_var0
//     },
//     {
//         .IPC_Variable   = &(Rxframe_456_var1),
//         .bitSize        =  6, 
//         .type           = UINT8 , 
//         .signalCallback = Cbk_RxSignal_456_var1
//     },
//     {
//         .IPC_Variable   = &(Rxframe_456_var2),
//         .bitSize        = 19, 
//         .type           = UINT32, 
//         .signalCallback = NULL
//     }
// };
// const uint8_t Frame456_IPC_byteSize = 4u; 

// Rxframe_IPC Frame789_IPC[] = {
//     {
//         .IPC_Variable   = &(Rxframe_789_var0),
//         .bitSize        =  5, 
//         .type           = UINT8,  
//         .signalCallback = NULL
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var1),
//         .bitSize        =  9, 
//         .type           = UINT16,  
//         .signalCallback = NULL
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var2),
//         .bitSize        =  3, 
//         .type           = UINT8,  
//         .signalCallback = Cbk_RxSignal_789_var2
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var3),
//         .bitSize        =  9, 
//         .type           = UINT16,  
//         .signalCallback = NULL
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var4),
//         .bitSize        = 13,
//         .type           = UINT16,  
//         .signalCallback = NULL
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var5),
//         .bitSize        = 19,
//         .type           = UINT32,  
//         .signalCallback = NULL
//     },

//     {
//         .IPC_Variable   = &(Rxframe_789_var6),
//         .bitSize        = 11,
//         .type           = UINT16,  
//         .signalCallback = Cbk_RxSignal_789_var6
//     }
// };
// const uint8_t Frame789_IPC_byteSize = 8u; 

// canIf_Rxframe CanIf_RxFrames[frameNo] = {
//     {
//         .canFrame = 
//         {
//             .can_id   = FrameID_123,
//             .can_dlc  = Frame123_IPC_byteSize
//         },
//         .IPC_variables   = Frame123_IPC,
//         .frameSignalNo   = (sizeof(Frame123_IPC) / sizeof(Rxframe_IPC)),
//         .frameRxCallback = Cbk_RxFrame_123
//     },

//     {
//         .canFrame = 
//         {
//             .can_id   = FrameID_456,
//             .can_dlc  = Frame456_IPC_byteSize
//         },
//         .IPC_variables   = Frame456_IPC,
//         .frameSignalNo   = (sizeof(Frame456_IPC) / sizeof(Rxframe_IPC)),
//         .frameRxCallback = NULL
//     },

//     {
//         .canFrame = 
//         {
//             .can_id   = FrameID_789,
//             .can_dlc  = Frame789_IPC_byteSize
//         },
//         .IPC_variables   = Frame789_IPC,
//         .frameSignalNo   = (sizeof(Frame789_IPC) / sizeof(Rxframe_IPC)),
//         .frameRxCallback = NULL
//     }
// };


#endif