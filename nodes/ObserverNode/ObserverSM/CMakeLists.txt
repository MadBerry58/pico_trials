add_library(ObserverSM_lib
    ObserverSM.h
    ObserverSM.c

    nodeSWC/controlLogicSM/controlLogicSM.h
    nodeSWC/controlLogicSM/controlLogicSM.c

    nodeSWC/encoderSM/encoderSM.h
    nodeSWC/encoderSM/encoderSM.c

    nodeSWC/warmLedSM/warmLedSM.h
    nodeSWC/warmLedSM/warmLedSM.c

    nodeSWC/coldLedSM/coldLedSM.h
    nodeSWC/coldLedSM/coldLedSM.c

    nodeSWC/lightSensSM/lightSensSM.h
    nodeSWC/lightSensSM/lightSensSM.c
    
    nodeSWC/motorControlSM/motorControlSM.h
    nodeSWC/motorControlSM/motorControlSM.c
    
    nodeSWC/pushButtonSM/pushButtonSM.h
    nodeSWC/pushButtonSM/pushButtonSM.c
    
    nodeSWC/rgb_stripSM/rgb_stripSM.h
    nodeSWC/rgb_stripSM/rgb_stripSM.c

    nodeSWC/rgb_ringSM/rgb_ringSM.h
    nodeSWC/rgb_ringSM/rgb_ringSM.c
    
    nodeSWC/tempSensSM/tempSensSM.h
    nodeSWC/tempSensSM/tempSensSM.h
)

target_link_libraries(ObserverSM_lib PUBLIC
    picoOS
)