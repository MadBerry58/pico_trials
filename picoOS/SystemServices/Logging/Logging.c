#include "Logging.h"

#define EVENT_BUFFER_SIZE_DEFAULT 256u
#define EVENT_BUFFER_SIZE  EVENT_BUFFER_SIZE_DEFAULT
#define EVENT_BUFFER_CIRCULAR

LogEvent_t OS_eventLog[EVENT_BUFFER_SIZE_DEFAULT];
size_t eventIndex = EVENT_BUFFER_SIZE_DEFAULT;

uint8_t log_event(LogEvent_t event)
{
    #ifdef EVENT_BUFFER_CIRCULAR
    OS_eventLog[eventIndex] = event;
    eventIndex = eventIndex % EVENT_BUFFER_SIZE;
    #else
    
    #endif
}

uint8_t get_events(LogEvent_t *outputBuffer)
{

}

uint8_t clear_events()
{
    uint8_t retVal = 0u;
    size_t index;

    for(index = 0u; index < EVENT_BUFFER_SIZE; ++index)
    {
        OS_eventLog[index] = {0};
    }

    return retVal;
}