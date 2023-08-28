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

target_link_libraries(HardwareLibrary PUBLIC 
        PioLibrary
)