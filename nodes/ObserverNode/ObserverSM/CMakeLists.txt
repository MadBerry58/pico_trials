add_library(ObserverSM_lib
    ObserverSM.h
    ObserverSM.c
)

target_link_libraries(ObserverSM_lib PUBLIC
    picoOS
)