add_library(WatchdogLibrary
    Watchdog.h
    Watchdog.c
)

target_link_libraries(WatchdogLibrary PUBLIC
    pico_stdlib
    hardware_watchdog
)