#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/rtc.h"

uint8_t EncoderSM_init(void);
uint8_t EncoderSM_run(uint *response);
