#ifndef LIGHT_SWITCH_DATA_H
#define LIGHT_SWITCH_DATA_H

#include <stdio.h>
#include "pico/stdlib.h"
#define SYSTEM_ID 0xFFu;

/* CAN Frames */

struct lightParameters_Rx_Frame_t
{
    const   uint32_t        can_id;
    struct  Rx_lightParameters_t
    {
            uint8_t         warmWhite_intensity   :  4;
            uint8_t         coldWhite_intensity   :  4;
            uint8_t         rgb_pattern_index     :  4;
            uint8_t         rgb_pattern_intensity :  4;
            uint64_t        filler                : 48;
    }                       lightParameters;

    const   uint8_t         dataBytes;

            bool            updateFlag;
    const   uint8_t         updateType;
    const   uint16_t        updateTimeMS;
            uint32_t        lastUpdate;
    const   void            (*callback)(void);
} lightParameters_Rx_Frame = 
{
    .can_id                     = 10,
    .lightParameters            = 
    {
        .warmWhite_intensity    = 0u,
        .coldWhite_intensity    = 0u,
        .rgb_pattern_index      = 0u,
        .rgb_pattern_intensity  = 0u,
    },
    .dataBytes                  = 2u,

    .updateFlag                 = false,
    .updateType                 = 0u,
    .updateTimeMS               = 100u,
    .lastUpdate                 = UINT32_MAX,
    .callback                   = NULL
};

struct systemCommunication_Rx_Frame_t
{
    const   uint32_t        can_id;
    struct  Rx_systemParameters_t
    {
            uint8_t         system_target         :  8;
            uint16_t        system_command        : 16;
            uint64_t        filler                : 40;
    } systemParameters;
    const   uint8_t         dataBytes;

            bool            updateFlag;
    const   FrameUpdate_t   updateType;
    const   uint16_t        updateTimeMS;
    const   void            (*callback)(void);
} systemCommunication_Rx_Frame = 
{
    .can_id             = 122,
    .systemParameters   = 
    {
        .system_target  = 11,
        .system_command = 12,
    },
    .dataBytes          = 3,

    .updateFlag         = false,
    .updateType         = 0u,
    .updateTimeMS       = 100u,
    .callback           = NULL
};

struct systemCommunication_Tx_Frame_t
{
    const   uint32_t        can_id;
    struct  Tx_systemParameters_t
    {
            uint8_t         node_ID               :  8;
            uint8_t         node_type             :  4;
            uint8_t         associated_node_ID    :  8;
            uint8_t         associated_node_type  :  4;
            uint8_t         core_temperature      :  6;
            uint8_t         cpu_usage             :  8;
            uint64_t        filler                : 26;
    } systemParameters ;
    const   uint8_t         dataBytes;

            bool            updateFlag;
    const   FrameUpdate_t   updateType;
    const   uint16_t        updateTimeMS;
    const   void            (*callback)(void);
} systemCommunication_Tx_Frame = 
{
    .can_id                   = 123u,
    .dataBytes                = 5,
    .systemParameters         = 
    {
        .node_ID              = 3u,
        .node_type            = 2u,
        .associated_node_ID   = 123u,
        .associated_node_type = 12u,
        .core_temperature     = 27u,
        .cpu_usage            = 0u
    },

    .updateFlag               = false,
    .updateType               = 0u,
    .updateTimeMS             = 100u,
    .callback                 = NULL
};

/* IPC variables */

uint8_t current_rgbPatternIndex     = 0u;
uint8_t current_warmWhiteIntensity  = 0u;
uint8_t current_coldWhiteIntensity  = 0u;

extern  uint8_t   encoderPosition;
extern  bool      encoderPosition_updateFlag;

extern  bool      buttonState;
extern  uint32_t  buttonTimePressed;
extern  bool      pushButton_updateFlag;



#endif