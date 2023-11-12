# add RTT driver folder
if (${MCU_FAMILY} STREQUAL  "CM0")
    add_subdirectory(SEGGER_RTT_M0)
elseif (${MCU_FAMILY} STREQUAL  "CM3")
    add_subdirectory(SEGGER_RTT_M3)
elseif (${MCU_FAMILY} STREQUAL  "CM4")
    add_subdirectory(SEGGER_RTT_M4)
endif()

# add another driver folder here
# add_subdirectory(ANY_DIR)
# ...

# inlude local cources if need
target_sources(${CURRENT_PROJECT_NAME}
    PRIVATE
        #add source here sorce.c
)

# inlude local headers if need
target_include_directories(${CURRENT_PROJECT_NAME}
    PRIVATE
		${CMAKE_CURRENT_LIST_DIR}
)