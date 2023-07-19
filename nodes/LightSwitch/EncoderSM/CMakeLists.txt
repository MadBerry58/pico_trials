add_library(EncoderSM_lib
    EncoderSM.h
    EncoderSM.c
)

target_link_libraries(EncoderSM_lib PUBLIC
    picoOS
    #hardware_ modules should be included from picoOS, or an API provided to replace them
    hardware_gpio
    hardware_pwm
    hardware_rtc
)