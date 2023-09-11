# add_subdirectory(logicSM)

add_executable(LightSwitch 
    logicSM/logicSM.h
    logicSM/logicSM.c
    LightSwitch_Node.h
    LightSwitch_Node.c
    )

target_link_libraries(LightSwitch PUBLIC
    # picoOS
)