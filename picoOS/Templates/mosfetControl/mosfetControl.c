#include "mosfetControl.h" 
#include "hardware/clocks.h"

#define NANOSECONDS_IN_SECOND 1000000000lu



uint8_t init_mosfetControl(MOSFET_specs *mosfet)
{
    uint8_t retVal = 0u;
    // uint16_t sysTickDuration_ns = NANOSECONDS_IN_SECOND / clock_get_hz(clk_sys);
    uint16_t minCycleTime;

    gpio_set_function(mosfet->controlPin, GPIO_FUNC_PWM);

    mosfet->config   = pwm_get_default_config();
    // mosfet->sliceNum = pwm_gpio_to_slice_num(mosfet->controlPin);
    
    mosfet->minPinHigh_ns = (
        mosfet->riseDelay_ns    +
        mosfet->riseTime_ns     +
        mosfet->minActiveTime_ns
    );

    mosfet->minPinLow_ns = (
        mosfet->fallDelay_ns    +
        mosfet->fallTime_ns     +
        mosfet->minInactiveTime_ns
    );

    minCycleTime = mosfet->minPinHigh_ns + mosfet->minPinLow_ns;
    mosfet->maxFrequency_hz = NANOSECONDS_IN_SECOND / minCycleTime;
    
    /* 
    Minimize thermal conversion
        Minimize time spent in rise cycle, 
            Minimize ON-OFF transition number
        Minimize ON time (lux sensor might be necessary for calibration)
    Minimize switching frequency to reduce induction effect in wires
     */

    // pwm_init(mosfet->sliceNum, &(mosfet->controlPin), false);

    return retVal;
}

uint8_t update_mosfetControl(MOSFET_specs *mosfet)
{
    uint8_t retVal = 0u;

    return retVal;
}