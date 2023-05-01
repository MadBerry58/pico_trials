#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef enum Event_Priority_e{
    Ev_Prio_IMIDIATE,
    Ev_Prio_HIGH,
    Ev_Prio_MODERATE,
    Ev_Prio_LOW,
    Ev_Prio_NONE
};

typedef enum Task_Priority_e{
    T_Prio_HIGH,
    T_Prio_MODERATE,
    T_Prio_LOW,
    T_Prio_NONE
};

typedef enum Event_Type_e
{
    Ev_Type_Undefined,
    Ev_Type_Acknowledge,
    Ev_Type_Response,
    Ev_Type_Request,
    Ev_Type_Error,
    Ev_Type_Panic
};

typedef struct Task_t{
    void *taskAdress            = nullptr;
    Task_Priority_e priority    = T_Prio_NONE;
    uint8 cycleTime             = 0ul; /* Time in MS */
    uint32 nextTrigger          = 0ul; /* Time till next trigger */
};

typedef struct Event_t{
    uint8 eventID               = 0u;
    Event_Type_e eventType      = Event_Undefined;
    Event_Priority_e priority   = Ev_Prio_NONE;
};

uint setEventNumbers(uint eventsNo);

uint addEvents(Event_t *events);

uint removeEvent();

uint updateEvents();

uint handleEvents();

uint addTasks(Task_t *tasks);

uint updateSchedule();

uint runSchedule();

