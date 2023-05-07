add_executable(devNode
    ${CMAKE_CURRENT_LIST_DIR}/devNode.h
    ${CMAKE_CURRENT_LIST_DIR}/devNode.c
)

target_link_libraries(devNode
    picoOS
)