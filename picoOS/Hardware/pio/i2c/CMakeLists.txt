add_library(pio_i2c_bus_scan
        i2c_bus_scan.c
        pio_i2c.c
        pio_i2c.h
)

pico_generate_pio_header(pio_i2c_bus_scan ${CMAKE_CURRENT_LIST_DIR}/i2c.pio OUTPUT_DIR ../generated)

target_link_libraries(pio_i2c_bus_scan PUBLIC 
        pico_stdlib 
        hardware_pio
)

