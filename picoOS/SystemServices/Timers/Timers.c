#include "Timers.h"
#include "pico/util/datetime.h"
#include "hardware/rtc.h"

#define YEAR_DEFAULT        2020u
#define MONTH_DEFAULT       06u
#define DAY_DEFAULT         05u
#define DOTW_DEFAULT        05u // 0 is Sunday, so 5 is Friday
#define HOUR_DEFAULT        15u
#define MIN_DEFAULT         45u
#define SEC_DEFAULT         00u
#define BUFFER_SIZE_DEFAULT 256u

datetime_t t = {
        .year  = YEAR_DEFAULT,
        .month = MONTH_DEFAULT,
        .day   = DAY_DEFAULT,
        .dotw  = DOTW_DEFAULT, 
        .hour  = HOUR_DEFAULT,
        .min   = MIN_DEFAULT,
        .sec   = SEC_DEFAULT
};

char datetime_buf[BUFFER_SIZE_DEFAULT];
char *datetime_str = &datetime_buf[0];


///TODO: Add RTC functionality

///TODO: Add RTC timeout functionality
///TODO: Add internal timeout functionality

Errors_OS_e init_Timers()
{
    uint8_t retVal = OS_E_OK;

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&t);

    return retVal;
}

uint8_t start_RTC()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t get_RTC(char *output_buf, size_t output_buf_size)
{
    uint8_t retVal = 0u;
    rtc_get_datetime(&t);
    datetime_to_str(output_buf, output_buf_size, &t);
    return retVal;
}

uint8_t sync_timer()
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t start_timer(uint32_t *timerVariable)
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t check_timer(uint32_t *timerVariable, uint32_t timeoutVal)
{
    uint8_t retVal = 0u;

    return retVal;
}