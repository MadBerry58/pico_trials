add_library(QuadratureEncoderSMLibrary
    QuadratureEncoderSM.h
    QuadratureEncoderSM.c
    )

target_link_libraries(QuadratureEncoderSM
    pico_stdlib
    )