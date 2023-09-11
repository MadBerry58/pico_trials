#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdio.h>
#include "../picoOS.h"

typedef enum 
{
    Ev_Prio_IMIDIATE,
    Ev_Prio_HIGH    ,
    Ev_Prio_MODERATE,
    Ev_Prio_LOW     ,
    Ev_Prio_NONE
} Event_Priority_e;

typedef enum 
{
    T_Prio_HIGH     ,
    T_Prio_MODERATE ,
    T_Prio_LOW      ,
    T_Prio_NONE
} Task_Priority_e;

typedef enum 
{
    Ev_Type_Undefined   ,
    Ev_Type_Acknowledge ,
    Ev_Type_Response    ,
    Ev_Type_Request     ,
    Ev_Type_Error       ,
    Ev_Type_Panic
} Event_Type_e;

typedef struct 
{
    void            (*taskFunction)(void)   ;
    uint8_t         taskID                  ;
    Task_Priority_e priority                ;
    uint8_t         cycleTime               ;
    uint32_t        nextTrigger             ;
} Task_t;

typedef struct 
{
    uint8_t             eventID  ;
    Event_Type_e        eventType;
    Event_Priority_e    priority ;
} Event_t;

uint8_t init_OS_scheduler   (Task_t *taskList                           );

uint8_t init_Node_Scheduler (Task_t *taskList                           );

uint8_t addEvent            (Event_t  event,    Event_t *eventList      );

uint8_t removeEvent         (uint8_t  eventID,  Event_t *eventList      );

uint8_t updateEvents        (Event_t *eventList                         );

uint8_t handleEvents        (Event_t *eventList                         );

uint8_t updateSchedule      (Task_t *taskList, Event_t *executionList   );

uint8_t runSchedule         (Task_t  *taskList                          );

#endif