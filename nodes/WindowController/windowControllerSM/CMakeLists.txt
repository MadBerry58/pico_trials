add_library(windowControllerSM_lib

    windowControllerSM.h
    windowControllerSM.c
    # configuration.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/motorControlSM/motorControlSM.h
    nodeSWC/motorControlSM/motorControlSM.c

    nodeSWC/tempSensSM/tempSensSM.h
    nodeSWC/tempSensSM/tempSensSM.c

    nodeSWC/pushButtonSM/pushButtonSM.h
    nodeSWC/pushButtonSM/pushButtonSM.c
)

target_link_libraries(windowControllerSM_lib PUBLIC
    picoOS
)