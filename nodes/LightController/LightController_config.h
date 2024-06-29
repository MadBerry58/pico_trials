#ifndef LIGHT_CONTROLLER_CONFIG_H
#define LIGHT_CONTROLLER_CONFIG_H

#include "../../picoOS/picoOS.h"

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

#endif