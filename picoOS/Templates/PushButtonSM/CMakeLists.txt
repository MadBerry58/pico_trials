add_library(PushButtonSMLibrary
    PushButtonSM.h
    PushButtonSM.c
    )

target_link_libraries(PushButtonSMLibrary
    pico_stdlib
    )