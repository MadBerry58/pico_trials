add_subdirectory(QuadratureEncoderSM)

add_library(Templates
    Templates.h
    Templates.c
)

target_link_libraries(Templates PUBLIC
    pico_multicore
    QuadratureEncoderSMLibrary
)