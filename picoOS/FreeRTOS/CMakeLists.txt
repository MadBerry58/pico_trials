include(FreeRTOS_Kernel_import.cmake)

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    include
    Scheduler
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)