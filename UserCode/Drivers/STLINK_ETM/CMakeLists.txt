
target_sources(${CURRENT_PROJECT_NAME}
    PRIVATE
        ETM_init.c
)

target_include_directories(${CURRENT_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

