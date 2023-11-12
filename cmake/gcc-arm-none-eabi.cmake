set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

# Default GCC settings
set(FLAGS
    "-fdata-sections -ffunction-sections --specs=nosys.specs -Wl,--gc-sections -Wa,-adhlns=$@.lst"
)

set(CPP_FLAGS
    ""
)

set(ASM_FLAGS
    "-O0 -Wall -g -ggdb -x assembler-with-cpp"
)

if (NOT ${MCU_FAMILY} STREQUAL "CM0")
    set(ASM_FLAGS ${ASM_FLAGS} " -munaligned-access")
endif()

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc ${FLAGS})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc ${ASM_FLAGS} ${FLAGS})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++ ${FLAGS} ${CPP_FLAGS})
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(CMAKE_EXECUTABLE_SUFFIX_ASM ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")
set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)