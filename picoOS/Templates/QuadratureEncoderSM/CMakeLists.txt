add_library(QuadratureEncoderSMLibrary
    QuadratureEncoderSM.h
    QuadratureEncoderSM.c
    )

target_link_libraries(QuadratureEncoderSMLibrary
    pico_stdlib
    hardware_pio
    )