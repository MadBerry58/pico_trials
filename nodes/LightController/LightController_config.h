#ifndef LIGHT_CONTROLLER_CONFIG_H
#define LIGHT_CONTROLLER_CONFIG_H

#include "../../picoOS/picoOS.h"
/* 
    pins:
    pin0 : debug TX (UART0)  <OS reserved>
    pin1 : debug RX (UART0)  <OS reserved>
    pin2 : 
    pin3 : 
    pin4 : 
    pin5 : 
    pin6 : 
    pin7 : 
    pin8 : 
    pin9 : 
    pin10: 
    pin11: 
    pin12: MOSFET_0   (PWM6)
    pin13: WS2812_0   (PIO1)
    pin14: MOSFET_1   (PWM7)
    pin15: WS2812_1   (PIO1)
    pin16: canSPI_RX  (SPI0) <OS reserved>
    pin17: canSPI_CSn (SPI0) <OS reserved>
    pin18: canSPI_SC  (SPI0) <OS reserved>
    pin19: canSPI_TX  (SPI0) <OS reserved>
    pin20: canSPI_INT        <OS reserved>
    pin21: 
    pin22: 
    pin23: 
    pin24: 
    pin25: 
    pin26: ADC_sampling      <OS reserved>
    pin27: ADC_sampling      <OS reserved>
    pin28: ADC_sampling      <OS reserved>
    pin29: ADC_sampling      <OS reserved>
    
 */

///TODO: bind unique id for every node
#define LIGHT_CONTROLLER_FRAME_ID   0b0000 0000 1000 0000 0000 0000 0000 0000
/* Watched frame ids: */
#define CORE_COMMAND                0b0000 0000 0000 0000 0000 0000 0000 0001
#define CORE_UPDATE                 0b0000 0000 0000 0000 0000 0000 0000 1000
#define CORE_UPDATE                 0b0000 0000 0000 0000 0000 0000 0000 1000
#define SWITCH_COMMAND              0b0000 0000 0000 0000 0001 0000 0000 0000
#define SWITCH_UPDATE               0b0000 0000 0000 0000 1000 0000 0000 0000



struct can_frame{
    uint32_t can_id;             // 32 bit CAN_ID + EFF/RTR/ERR flags 
    uint8_t  can_dlc;            // frame payload length in byte (0 .. CAN_MAX_DLEN)
    uint8_t  data[8];            // max data length is 8
} 
lightControllerFrame =
{
    .can_id  = 0b0000 0000 0000 0000 0000 0000 0000 0000,
    .can_dlc = 8,
    .data    = 8
};

/* 
    [Node Status           ]    [Pattern Parameter     ]
    [Active pattern Index  ]    [Pattern intensity     ]
    [0]    [0]    [0]    [0]    [0]    [0]    [0]    [0]
    [0]    [0]    [0]    [0]    [0]    [0]    [0]    [0]
    [0]    [0]    [0]    [0]    [0]    [0]    [0]    [0]
    [0]    [0]    [0]    [0]    [0]    [0]    [0]    [0]
    [0]    [0]    [0]    [0]    [0]    [0]    [0]    [0]
*/

#endif