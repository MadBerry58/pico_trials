add_library(TimerLibrary
    Timers.h
    Timers.c
)

target_link_libraries(TimerLibrary PUBLIC
    pico_stdlib 
    hardware_rtc
)