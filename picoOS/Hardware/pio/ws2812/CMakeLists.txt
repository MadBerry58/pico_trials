add_library(pio_ws2812 ws2812.c)

file(MAKE_DIRECTORY ../generated)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(pio_ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pio_ws2812 PUBLIC 
        pico_stdlib 
        hardware_pio
)

add_library(pio_ws2812_parallel)

pico_generate_pio_header(pio_ws2812_parallel ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(pio_ws2812_parallel PRIVATE
        PIN_DBG1=3)

target_link_libraries(pio_ws2812_parallel PUBLIC 
        pico_stdlib 
        hardware_pio 
        hardware_dma
)