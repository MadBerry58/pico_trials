add_library(pio_quadrature_encoder)

pico_generate_pio_header(pio_quadrature_encoder ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pio_quadrature_encoder PUBLIC
        pico_stdlib
        hardware_pio
)