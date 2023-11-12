#if(CONFIG_BSP_IFACE_SEGGER)
    target_sources(${CURRENT_PROJECT_NAME}
        PRIVATE
            SEGGER_RTT_ASM_ARMv7M.S
            SEGGER_RTT_printf.c
            SEGGER_RTT.c

            SEGGER_RTT_Syscalls_GCC.c
            SEGGER_RTT_Syscalls_IAR.c
            SEGGER_RTT_Syscalls_KEIL.c
    )

    target_include_directories(${CURRENT_PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}
    )
#endif()
