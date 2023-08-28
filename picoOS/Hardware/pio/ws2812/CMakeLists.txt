add_library(pio_ws2812 
        ws2812.h        
        ws2812.c
        )

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(pio_ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pio_ws2812 PUBLIC 
        pico_stdlib 
        hardware_pio
        hardware_dma
)