add_subdirectory(ADC)
add_subdirectory(GPIO)
add_subdirectory(PWM)

add_library(PinControlLibrary
    PinControl.h
    PinControl.c
)