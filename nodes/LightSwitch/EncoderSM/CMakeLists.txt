add_library(EncoderSM_lib
    EncoderSM.h
    EncoderSM.c
)

target_link_libraries(EncoderSM_lib PUBLIC
    picoOS
    hardware_gpio
    hardware_pwm
    hardware_rtc
)