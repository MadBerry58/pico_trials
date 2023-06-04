add_subdirectory(dma)
add_subdirectory(interrupts)
add_subdirectory(memory)
add_subdirectory(peripherals)
add_subdirectory(pio)
add_subdirectory(sio)

add_library(HardwareLibrary
    Hardware.c
    Hardware.h
)

# target_include_directories(HardwareLibrary PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/pio
#     )

target_link_libraries(HardwareLibrary PUBLIC 
        PioLibrary
        # pico_stdlib 
        # hardware_pio
        # hardware_gpio
)