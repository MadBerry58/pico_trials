#include "Scheduler.h"

#define MAX_TASKS  32
#define MAX_EVENTS 32

Event_t event_list [MAX_EVENTS];
Task_t  task_list  [MAX_TASKS];
uint activeEvents = 0u;

uint setEventNumbers(uint eventsNo)
{
    uint retVal = 1;
    if(eventsNo <= MAX_EVENTS)
    {
        activeEvents = eventNo;
        retVal = 0;
    }
}

int updateEvents()
{
    for(int i = 0u; i < eventNo; ++i)
    {
        
    }
}

int handleEvents()
{
    //reset watchdog
    for(int i = 0u; i < eventNo; ++i)
    {
        switch(event_list[i].eventType)
        {
            
        }
    }
}

int updateSchedule()
{

}

int runSchedule()
{
    retVal = 0u;
    //reset watchdog
    for(int i = 0u; i < eventNo; ++i)
    {
        task_list[i]->taskAdress();
    }
    return retVal;
}