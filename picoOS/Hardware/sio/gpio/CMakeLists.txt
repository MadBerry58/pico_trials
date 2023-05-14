add_library(gpio
    gpio.h
    gpio.c
)

target_link_libraries(gpio PUBLIC
    pico_stdlib 
    hardware_gpio
)