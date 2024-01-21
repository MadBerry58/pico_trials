add_subdirectory(ledTesterSM)

add_executable(ledTesterNode 
    ledTester_config.h
    ledTester_Node.c
)

target_link_libraries(ledTesterNode PUBLIC
    ledTesterSM_lib
)

pico_add_extra_outputs(ledTesterNode)