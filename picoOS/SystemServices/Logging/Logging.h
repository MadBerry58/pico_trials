#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

typedef struct LogEvent_t
{
    uint8_t componentID;
    uint8_t errorCode; 
};


uint8_t log_event(LogEvent_t event);

uint8_t get_events(LogEvent_t *outputBuffer);

uint8_t clear_events();

#endif