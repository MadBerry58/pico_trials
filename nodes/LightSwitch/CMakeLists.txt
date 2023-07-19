add_subdirectory(EncoderSM)

add_executable(LightSwitch 
    LightSwitch_Node.h
    LightSwitch_Node.c
    )

target_link_libraries(LightSwitch PUBLIC
    EncoderSM_lib
    # picoOS
)