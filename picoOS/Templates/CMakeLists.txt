add_subdirectory(mosfetControl)
add_subdirectory(QuadratureEncoderSM)

add_library(TemplateLibrary
    Templates.h
    Templates.c
)

target_link_libraries(TemplateLibrary PUBLIC
    MosfetControlLibrary
    QuadratureEncoderSMLibrary
)