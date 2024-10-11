#ifndef FREERTOS_SCHEDULER_CONFIG_H
#define FREERTOS_SCHEDULER_CONFIG_H

/* Scheduler Related */
#define configUSE_PREEMPTION                    1
#define configUSE_TICKLESS_IDLE                 0
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                    32
#define configMINIMAL_STACK_SIZE                ( configSTACK_DEPTH_TYPE ) 512 
#define configUSE_16_BIT_TICKS                  0

#endif /* FREERTOS_CONFIG_H */