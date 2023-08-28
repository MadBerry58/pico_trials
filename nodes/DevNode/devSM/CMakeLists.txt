add_library(devSM_lib
    devSM.h
    devSM.c
    configuration.h
)

target_link_libraries(devSM_lib PUBLIC
    picoOS
)