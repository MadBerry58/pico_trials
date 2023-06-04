add_library(pio_i2c
        pio_i2c.c
        pio_i2c.h
        i2c_bus_scan.c
)

pico_generate_pio_header(pio_i2c ${CMAKE_CURRENT_LIST_DIR}/i2c.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pio_i2c PUBLIC 
        pico_stdlib 
        hardware_pio
)

