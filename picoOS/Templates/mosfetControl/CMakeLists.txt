add_library(MosfetControlLibrary
    mosfetControl.h
    mosfetControl.c
)

target_link_libraries(MosfetControlLibrary PUBLIC
    pico_stdlib
    hardware_clocks
    hardware_pwm
)