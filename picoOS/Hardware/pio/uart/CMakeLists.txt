add_library(pio_uart_rx uart_rx.c)
add_library(pio_uart_tx uart_tx.c)

file(MAKE_DIRECTORY ../generated)
pico_generate_pio_header(pio_uart_rx ${CMAKE_CURRENT_LIST_DIR}/uart_rx.pio OUTPUT_DIR ../generated)
pico_generate_pio_header(pio_uart_tx ${CMAKE_CURRENT_LIST_DIR}/uart_tx.pio OUTPUT_DIR ../generated)

target_link_libraries(pio_uart_rx PUBLIC
        pico_stdlib
        pico_multicore
        hardware_pio
        )

target_link_libraries(pio_uart_tx PUBLIC 
        pico_stdlib 
        hardware_pio
        )
