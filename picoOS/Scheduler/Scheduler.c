#include "Scheduler.h"

uint activeEvents = 0u;


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