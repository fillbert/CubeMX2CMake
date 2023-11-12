#if(CONFIG_BSP_IFACE_SEGGER)
    target_sources(${CURRENT_PROJECT_NAME}
        PRIVATE
                SEGGER_RTT_printf.c
                SEGGER_RTT.c
    )

    target_include_directories(${CURRENT_PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}
    )
#endif()
