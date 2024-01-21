add_library(ledTesterSM_lib
    ledTesterSM.h
    ledTesterSM.c

    nodeSWC/controlLogicSM/controlLogicSM.h
    nodeSWC/controlLogicSM/controlLogicSM.c

    nodeSWC/encoderSM/encoderSM.h
    nodeSWC/encoderSM/encoderSM.c

    nodeSWC/warmLedSM/warmLedSM.h
    nodeSWC/warmLedSM/warmLedSM.c

    nodeSWC/coldLedSM/coldLedSM.h
    nodeSWC/coldLedSM/coldLedSM.c

    nodeSWC/pushButtonSM/pushButtonSM.h
    nodeSWC/pushButtonSM/pushButtonSM.c
)

target_link_libraries(ledTesterSM_lib PUBLIC
    picoOS
)