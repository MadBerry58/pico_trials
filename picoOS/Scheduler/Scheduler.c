#include "Scheduler.h"

/**
 * @brief Populate OS schedule queues
 * 
 * @param taskList 
 * @return uint8_t 
 */
uint8_t init_OS_scheduler   (Task_t *taskList)
{
    uint8_t retVal = 0u;
    
    return retVal;
}

/**
 * @brief Populate node schedule queues
 * 
 * @param taskList 
 * @return uint8_t 
 */
uint8_t init_Node_Scheduler (Task_t *taskList)
{
    uint8_t retVal = 0u;

    return retVal;
}

uint8_t updateEvents        (Event_t *eventList, Event_t *executionList)
{
    uint8_t retVal = 0u;

    /* 
    for(events in eventList)
        if(nextTriggerTime > currentTime) && (oldState != currentState)
            add event to executionList
     */

    return retVal;
}

uint8_t handleEvents        (Event_t *executionList)
{
    uint8_t retVal = 0u;
    /* 
    for(events in executionList)
        run event function
     */
    return retVal;
}

uint8_t updateSchedule      (Task_t *taskList, Event_t *executionList)
{
    uint8_t retVal = 0u;

    /* 
    for(task in taskList)
        if(nextTriggerTime > currentTime) && (oldState != currentState)
            add task to executionList
     */
    return retVal;
}

uint8_t runSchedule         (Task_t *taskList)
{
    uint8_t retVal = 0u;
    /* 
    for(events in executionList)
        run event function
     */
    return retVal;
}

uint8_t addEvent            (Event_t event, Event_t *eventList)
{
    uint8_t retVal = 0;
    
    return retVal;
}

uint8_t removeEvent         (uint8_t eventID, Event_t *eventList)
{
    uint8_t retVal = 0u;

    return retVal;
}

/**
 * @brief Bind Event handler to system interrupt
 * 
 */
static uint8_t bindInterruptEvent()
{
    uint8_t retVal = 0;

    return retVal;
}