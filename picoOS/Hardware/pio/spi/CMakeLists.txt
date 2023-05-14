add_library(pio_spi_flash
        spi_flash.c
        pio_spi.c
        pio_spi.h
)

add_library(pio_spi_loopback
        spi_loopback.c
        pio_spi.c
        pio_spi.h
)

pico_generate_pio_header(pio_spi_flash ${CMAKE_CURRENT_LIST_DIR}/spi.pio OUTPUT_DIR ../generated)
pico_generate_pio_header(pio_spi_loopback ${CMAKE_CURRENT_LIST_DIR}/spi.pio OUTPUT_DIR ../generated)

target_link_libraries(pio_spi_flash PUBLIC 
        pico_stdlib 
        hardware_pio
)

target_link_libraries(pio_spi_loopback PUBLIC 
        pico_stdlib 
        hardware_pio
)