add_library(ServoControlLibrary
    servoControl.h
    servoControl.c
)

target_link_libraries(ServoControlLibrary PUBLIC
    pico_stdlib
    hardware_pwm
)