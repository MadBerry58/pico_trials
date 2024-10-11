add_subdirectory(FreeRTOS)
add_subdirectory(Hardware)
add_subdirectory(InterruptHandling)
add_subdirectory(FlashControl)
add_subdirectory(SystemServices)
add_subdirectory(Templates)
add_subdirectory(Comm)

add_library(picoOS
    picoOS.h
    picoOS.c
    picoOS_Types.h
    canDB.h
)

target_link_libraries(picoOS PUBLIC
    pico_multicore
    freertos_config
    pico_async_context_freertos
    FreeRTOS-Kernel-Heap4

    IRQLibrary
    CommLibrary
    ErrorLibrary
    FlashLibrary
    HardwareLibrary
    TimerLibrary
    WatchdogLibrary
    TemplateLibrary
)