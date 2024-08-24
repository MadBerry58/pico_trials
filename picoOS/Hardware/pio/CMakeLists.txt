add_subdirectory(ws2812)
add_subdirectory(quadrature_encoder)

add_library(PioLibrary
    pio.h
    pio_sm_costs.h
)
target_link_libraries(PioLibrary PUBLIC
    pio_ws2812
    pio_quadrature_encoder
)