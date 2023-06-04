add_library(pio_can
        can2040.h
        can2040.c
)

pico_generate_pio_header(pio_can ${CMAKE_CURRENT_LIST_DIR}/can2040.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pio_can PUBLIC 
        pico_stdlib 
        hardware_pio
        hardware_sync
)

