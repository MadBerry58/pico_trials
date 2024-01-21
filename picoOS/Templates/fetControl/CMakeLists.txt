add_library(FetControlLibrary
    fetControl.h
    fetControl.c
)

target_link_libraries(FetControlLibrary PUBLIC
    pico_stdlib
    hardware_clocks
    hardware_pwm
)