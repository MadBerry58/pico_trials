#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/rtc.h"

int EncoderSM_init(void);
int EncoderSM_run(uint *response);
