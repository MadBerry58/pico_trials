add_library(Hardware_peripheralsLibrary
    peripherals.c
    peripherals.h
)

target_link_libraries(Hardware_peripheralsLibrary PUBLIC
    pico_stdlib 
    hardware_i2c
    hardware_uart
    hardware_spi
)