add_subdirectory(Hardware)
add_subdirectory(InterruptHandling)
add_subdirectory(FlashControl)
add_subdirectory(Scheduler)
add_subdirectory(SystemServices)
add_subdirectory(Templates)
add_subdirectory(Comm)

add_library(picoOS
    picoOS.h
    picoOS.c
    picoOS_Types.h
    canDB.h
)

target_link_libraries(picoOS PUBLIC
    pico_multicore

    IRQLibrary
    CommLibrary
    ErrorLibrary
    FlashLibrary
    HardwareLibrary
    SchedulerLibrary
    TimerLibrary
    WatchdogLibrary
    TemplateLibrary
)