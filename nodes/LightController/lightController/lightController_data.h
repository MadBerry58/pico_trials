#ifndef LIGHT_CONTROLLER_DATA_H
#define LIGHT_CONTROLLER_DATA_H

#include <stdio.h>
#define SYSTEM_ID 0xFFu;

/* CAN Frames */

struct lightParameters_Rx_Frame_t
{
          uint32_t        can_id;
  const   uint8_t         dataBytes;
  struct  Rx_lightParameters_t
  {
    uint8_t  warmWhite_intensity   :  4;
    uint8_t  coldWhite_intensity   :  4;
    uint8_t  rgb_pattern_index     :  4;
    uint8_t  rgb_pattern_intensity :  4;
    uint64_t filler                : 48;
  } lightParameters;
} lightParameters_Rx_Frame = 
{
  .can_id                   = 9,
  .dataBytes                = 2u,
  .lightParameters          = 
  {
    .warmWhite_intensity    = 0u,
    .coldWhite_intensity    = 0u,
    .rgb_pattern_index      = 0u,
    .rgb_pattern_intensity  = 0u
  }
};

struct lightParameters_Tx_Frame_t
{
  uint32_t        can_id;
  uint8_t         dataBytes;
  struct  Tx_lightParameters_t
  {
    uint8_t  warmWhite_intensity   :  4;
    uint8_t  coldWhite_intensity   :  4;
    uint8_t  rgb_pattern_index     :  4;
    uint8_t  rgb_pattern_intensity :  4;
    uint64_t filler                : 48;
  } lightParameters;
} lightParameters_Tx_Frame = 
{
  .can_id                   = 10,
  .dataBytes                = 14,
  .lightParameters          = 
  {
    .warmWhite_intensity    = 0u,
    .coldWhite_intensity    = 0u,
    .rgb_pattern_index      = 0u,
    .rgb_pattern_intensity  = 0u
  }
};

struct systemCommunication_Rx_Frame_t
{
  const   uint32_t        can_id;
  const   uint8_t         dataBytes;
  struct  Rx_systemParameters_t
  {
    uint8_t  system_target         :  8;
    uint16_t system_command        : 16;
    uint64_t filler                : 40;
  } systemParameters;
} systemCommunication_Rx_Frame = 
{
  .can_id           = 122,
  .dataBytes        = 3,
  .systemParameters = 
  {
    .system_target  = 11,
    .system_command = 12,
  }
};

struct systemCommunication_Tx_Frame_t
{
          uint32_t        can_id;
  const   uint8_t         dataBytes;
  struct  Tx_systemParameters_t
  {
    uint8_t  node_ID               :  8;
    uint8_t  node_type             :  4;
    uint8_t  associated_node_ID    :  8;
    uint8_t  associated_node_type  :  4;
    uint8_t  core_temperature      :  6;
    uint8_t  cpu_usage             :  8;
    uint64_t filler                : 26;
  } systemParameters ;
} systemCommunication_Tx_Frame = 
{
  .can_id                 = 123u,
  .dataBytes              = 5,
  .systemParameters       = 
  {
    .node_ID              = 3u,
    .node_type            = 2u,
    .associated_node_ID   = 123u,
    .associated_node_type = 12u,
    .core_temperature     = 27u,
    .cpu_usage            = 0u
  }
};

/* IPC variables */

uint8_t current_rgbPatternIndex     = 0u;
uint8_t current_warmWhiteIntensity  = 0u;
uint8_t current_coldWhiteIntensity  = 0u;

#endif