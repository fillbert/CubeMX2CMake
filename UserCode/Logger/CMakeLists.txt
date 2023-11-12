target_sources(${CURRENT_PROJECT_NAME}
    PRIVATE
        Logger.c
)

target_include_directories(${CURRENT_PROJECT_NAME}
    PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
)