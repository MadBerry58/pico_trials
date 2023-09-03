add_subdirectory(can)
add_subdirectory(ws2812)
add_subdirectory(uart)
add_subdirectory(spi)
add_subdirectory(i2c)
add_subdirectory(quadrature_encoder)

add_library(PioLibrary
    pio.h
    pio_sm_costs.h
)
target_link_libraries(PioLibrary PUBLIC
    pio_i2c
    pio_uart_rx
    pio_uart_tx
    pio_spi_flash
    pio_spi_loopback
    pio_ws2812
    pio_quadrature_encoder
)

target_link_libraries(PioLibrary PUBLIC
    optimized pio_can
)