add_subdirectory(devSM)

add_executable(devNode
    ${CMAKE_CURRENT_LIST_DIR}/devNode.c
)

target_link_libraries(devNode PUBLIC
    picoOS
    devSM_lib
)