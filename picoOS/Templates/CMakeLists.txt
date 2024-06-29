add_subdirectory(fetControl)
add_subdirectory(QuadratureEncoderSM)
add_subdirectory(PushButtonSM)
add_subdirectory(servoControl)

add_library(TemplateLibrary
    Templates.h
    Templates.c
)

target_link_libraries(TemplateLibrary PUBLIC
    FetControlLibrary
    QuadratureEncoderSMLibrary
    PushButtonSMLibrary
    ServoControlLibrary
)