add_subdirectory(Comm)
add_subdirectory(ErrorHandling)
add_subdirectory(FlashControl)
add_subdirectory(Hardware)
add_subdirectory(Scheduler)
add_subdirectory(Timers)
add_subdirectory(Watchdog)

add_library(picoOS
    picoOS.h
    picoOS.c
)

target_link_libraries(picoOS PUBLIC
    pico_multicore
    CommLibrary
    ErrorLibrary
    FlashLibrary
    HardwareLibrary
    SchedulerLibrary
    TimerLibrary
    WatchdogLibrary

    hardware_pwm
)