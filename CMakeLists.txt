# ##############################################################################
#                Copyright filbertby(c) 2023 filbertby@gmail.com
# ##############################################################################

# ##############################################################################
#                        USER       CONFIG     SECTION
# ##############################################################################
cmake_minimum_required(VERSION 3.20)
# if you want to use only makefile setting make this flag ON
# Otherwise set it  OFF and make all settings manually below
set(GET_ALL_SETTINGS_FROM_MAKEFILE OFF)

# set project name
set(CURRENT_PROJECT_NAME test-app)

# sec CUBE-MX folder name
set(CUBEMX_PROJECT_NAME test105)

# set MCU famely [value needs to be set according your CPU core]
# set(MCU_FAMILY CM0)
set(MCU_FAMILY CM3)
# set(MCU_FAMILY CM4)

# set user code dir mane
set(USER_PROJECT_CODE UserCode)

# Set languages restrictions here
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# ##############################################################################
# ##############################################################################
# ##############################################################################
# save platform name
set(CURRENT_PLATFORM_UNIX ${UNIX})
# add toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_HOME_DIRECTORY}/cmake/gcc-arm-none-eabi.cmake)

project(${CURRENT_PROJECT_NAME}
    VERSION 0.0.1
	LANGUAGES C CXX ASM
)

# include modules folder
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

# Manage all the Kconfig routines
include(cmake/top.cmake)

# set directory pathes
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${USER_PROJECT_CODE})
set(CUBEMX_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME})

# ##############################################################################
# Edit your CPU_PARAMETERS up to the next border if needs
set(CPU_PARAMETERS
    -mthumb
    $<$<STREQUAL:${MCU_FAMILY},CM0>:-mcpu=cortex-m0>
    $<$<STREQUAL:${MCU_FAMILY},CM3>:-mcpu=cortex-m3>
    $<$<STREQUAL:${MCU_FAMILY},CM4>:-mcpu=cortex-m4>
    $<$<NOT:$<STREQUAL:${MCU_FAMILY},CM0>>:-mfloat-abi=soft>
    $<$<NOT:$<STREQUAL:${MCU_FAMILY},CM0>>:-mfpu=fpv4-sp-d16>
)
# ##############################################################################
# GRABBING MAKEFILE VARIABLES
include(MakeFileGrabber)
Grab_Makefile()

# ##############################################################################
# add exacutable name
set(EXECUTABLE ${CMAKE_PROJECT_NAME})

# Executable files
add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES}
    ${STARTUP_SCRIPT}
)

# add user code
add_subdirectory(${USER_PROJECT_CODE})

# Embedded macros (defines)
target_compile_definitions(${EXECUTABLE}
    PRIVATE
        ${C_DEFS}
)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE}
    PRIVATE
        ${CUBEMX_INCLUDE_DIRECTORIES}
)

# Compiler and linker options
target_compile_options(${EXECUTABLE}
    PRIVATE
    # grabbed from makefile
    $<$<BOOL:${GET_ALL_SETTINGS_FROM_MAKEFILE}>: ${CFLAGS}>
    # manual mode
    $<$<NOT:$<BOOL:${GET_ALL_SETTINGS_FROM_MAKEFILE}>>:
        ${CPU_PARAMETERS}
        -Wall
        -Wextra
        -Wpedantic
        -Wno-unused-parameter
        $<$<NOT:$<STREQUAL:${MCU_FAMILY},CM0>>:-munaligned-access>
        -I "${CMAKE_BINARY_DIR}/kconfig/include/generated"
        $<$<COMPILE_LANGUAGE:CXX>:
            -Wno-volatile
            -Wold-style-cast
            -Wuseless-cast
            -Wsuggest-override>
        $<$<CONFIG:Debug>:-Og -g3 -ggdb>
        $<$<CONFIG:Release>:-Og -g0>
    >
    # common rules
    -I "${CMAKE_BINARY_DIR}/kconfig/include/generated"
)

# setup linker options
target_link_options(${EXECUTABLE}
    PRIVATE
        # grabbed from makefile
        $<$<BOOL:${GET_ALL_SETTINGS_FROM_MAKEFILE}>: ${LDFLAGS} ${CFLAGS}>
        # manual mode
        $<$<NOT:$<BOOL:${GET_ALL_SETTINGS_FROM_MAKEFILE}>>: ${CPU_PARAMETERS}>
        # common rules
        -Wl,--gc-sections
        -T${MCU_LINKER_SCRIPT}
        -Wl,--start-group
        -lc
        -lstdc++
        -Wl,--end-group
        -Wl,--print-memory-usage
        -Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

# get saize of the executable
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# make postbuild to generate hex and bin files
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin
)
