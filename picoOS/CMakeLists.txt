add_subdirectory(Comm)
add_subdirectory(FlashControl)
add_subdirectory(Hardware)
add_subdirectory(Scheduler)
add_subdirectory(Templates)
add_subdirectory(SystemServices)

add_library(picoOS
    picoOS.h
    picoOS.c
)

target_link_libraries(picoOS PUBLIC
    pico_multicore

    CommLibrary
    ErrorLibrary
    TemplateLibrary
    FlashLibrary
    HardwareLibrary
    SchedulerLibrary
    TimerLibrary
    WatchdogLibrary
)