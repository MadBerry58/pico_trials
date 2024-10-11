#include "Scheduler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pico/async_context_freertos.h"




/* **************************** */
/* Tasks */
/* **************************** */
// Priorities of our threads - higher numbers are higher priority
#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )
#define WORKER_TASK_PRIORITY    ( tskIDLE_PRIORITY + 4UL )

// Stack sizes of our threads in words (4 bytes)
#define MAIN_TASK_STACK_SIZE    configMINIMAL_STACK_SIZE
#define BLINK_TASK_STACK_SIZE   configMINIMAL_STACK_SIZE
#define WORKER_TASK_STACK_SIZE  configMINIMAL_STACK_SIZE

static async_context_freertos_t async_context_instance;
// Create an async context
static async_context_t *example_async_context(void) 
{
    async_context_freertos_config_t config                  = async_context_freertos_default_config();
                                    
    config.task_priority    = WORKER_TASK_PRIORITY;     // defaults to ASYNC_CONTEXT_DEFAULT_FREERTOS_TASK_PRIORITY
    config.task_stack_size  = WORKER_TASK_STACK_SIZE;   // defaults to ASYNC_CONTEXT_DEFAULT_FREERTOS_TASK_STACK_SIZE
    
    if (!async_context_freertos_init(&async_context_instance, &config))
    {
        return NULL;
    }

    return &async_context_instance.core;
}

static void do_work(async_context_t *context, async_at_time_worker_t *worker) 
{
    static uint32_t count = 0;

    async_context_add_at_time_worker_in_ms(context, worker, 10000);

    printf("Hello from worker count=%u\n", count++);

#if configNUMBER_OF_CORES > 1
        static int last_core_id = -1;
        
        if (portGET_CORE_ID() != last_core_id) 
        {
            last_core_id = portGET_CORE_ID();
            printf("worker is on core %d\n", last_core_id);
        }
#endif
}

async_at_time_worker_t worker_timeout = { .do_work = do_work };

void main_task(__unused void *params) 
{
    async_context_t    *context         = example_async_context();
    static  int         last_core_id    = -1;
            int         count           = 0;

    // start the worker running
    async_context_add_at_time_worker_in_ms(context, &worker_timeout, 0);

#if USE_LED
    // start the led blinking
    xTaskCreate(blink_task, "BlinkThread", BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);
#endif

    while(true) 
    {
#if configNUMBER_OF_CORES > 1
        if (portGET_CORE_ID() != last_core_id) 
        {
            last_core_id = portGET_CORE_ID();
            printf("main task is on core %d\n", last_core_id);
        }
#endif
        printf("Hello from main task count=%u\n", count++);
        vTaskDelay(3000);
    }
    async_context_deinit(context);
}

void vLaunch( void) 
{
    TaskHandle_t task;
    xTaskCreate(main_task, "MainThread", MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);

#if ((configUSE_CORE_AFFINITY && configNUMBER_OF_CORES) > 1)
    // we must bind the main task to one core (well at least while the init is called)
    vTaskCoreAffinitySet(task, 1);
#endif

    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}


/**
 * @brief Populate OS schedule queues
 * 
 * @param taskList 
 * @return uint8_t 
 */
Errors_OS_e init_OS_scheduler (void)
{
    Errors_OS_e retVal = 0u;
    
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
    uint8_t retVal = OS_E_OK;

    return retVal;
}

uint8_t updateEvents        (Event_t *eventList)
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