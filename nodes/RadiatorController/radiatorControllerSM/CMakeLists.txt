add_library(radiatorControllerSM_lib
    radiatorControllerSM.h
    radiatorControllerSM.c
    # configuration.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/motorControlSM/motorControlSM.h
    nodeSWC/motorControlSM/motorControlSM.c

    nodeSWC/tempSensSM/tempSensSM.h
    nodeSWC/tempSensSM/tempSensSM.c
)

target_link_libraries(radiatorControllerSM_lib PUBLIC
    picoOS
)