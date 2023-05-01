cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(Pico_Trials C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

set(ExtraFiles
    /**
    # EncoderSM.h
    # EncoderSM.c
    # Comms.h
    # Comms.c
    # ws2812_api.h
    # ws2812_api.c
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/generated)

add_executable(LightSwitch_Node
    LightSwitch_Node.c
    ${ExtraFiles}
	)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(LightSwitch_Node ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_link_libraries(LightSwitch_Node 
    pico_stdlib
    hardware_pwm
    hardware_rtc
    hardware_i2c
    hardware_dma
    hardware_pio
)


pico_enable_stdio_usb(LightSwitch_Node 1)
pico_enable_stdio_uart(LightSwitch_Node 1)

pico_add_extra_outputs(LightSwitch_Node)