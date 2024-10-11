add_library(SchedulerLibrary
    Scheduler.h
    Scheduler.c
)

target_link_libraries(SchedulerLibrary
    picoOS
    )