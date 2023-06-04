#ifndef PIO_H
#define PIO_H

#define PIO_CAN
#define PIO_I2C
#define PIO_QUADRATURE_ENCODER
#define PIO_SPI
#define PIO_UART
#define PIO_UART
#define PIO_WS2812

#ifdef PIO_CAN
#include "can/can2040.h"
#endif

#ifdef PIO_I2C
#include "i2c/pio_i2c.h"
#endif

#ifdef PIO_QUADRATURE_ENCODER
#include "quadrature_encoder/quadrature_encoder.pio.h"
#endif

#ifdef PIO_SPI
#include "spi/pio_spi.h"
#endif

#ifdef PIO_UART
#include "uart/uart_rx.pio.h"
#include "uart/uart_tx.pio.h"
#endif

#ifdef PIO_WS2812
#include "ws2812/ws2812.h"
#endif

#endif