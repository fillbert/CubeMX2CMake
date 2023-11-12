# ##############################################################################
#                 Copyright filbertby(c) 2023 filbertby@gmail.com
# ##############################################################################
# funstion to grab variable from make file
function(MakeFileVariableGrabber PathToMakeFIle VarName OutVariable)
    # make coomand to evaluare makefile on the fly
    set(mkcmd "make --eval='print-var: ; @echo $(${VarName})' print-var")

    # grab variable value
    execute_process(COMMAND CMD /c "${mkcmd}"
        OUTPUT_VARIABLE  ${OutVariable}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        WORKING_DIRECTORY ${PathToMakeFIle}
    )
    # export valuer
    set(${OutVariable} "${${OutVariable}}" PARENT_SCOPE)
endfunction()
# ##############################################################################

function(Grab_Makefile)
    # export asm startup file
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} ASM_SOURCES ASM_SOURCES)
    set(STARTUP_SCRIPT ${CUBEMX_DIR}/${ASM_SOURCES} PARENT_SCOPE)

    # export linker script
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} LDSCRIPT LDSCRIPT)
    set(MCU_LINKER_SCRIPT ${CUBEMX_DIR}/${LDSCRIPT} PARENT_SCOPE)

    # export compiller c/c++ flags
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} CFLAGS CFLAGS)
    separate_arguments(CFLAGS)
    set(CFLAGS ${CFLAGS} PARENT_SCOPE)

    # export assembler flags
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} ASFLAGS ASFLAGS)
    separate_arguments(ASFLAGS)
    set(ASFLAGS ${ASFLAGS} PARENT_SCOPE)

    # export linker flags
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} LDFLAGS LDFLAGS)
    set(LDFLAGS ${LDFLAGS} PARENT_SCOPE)

    # export project definitions
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} C_DEFS C_DEFS)
    set(C_DEFS ${C_DEFS} PARENT_SCOPE)

    # export sources -------------------------------
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} C_SOURCES STM32CUBEMX_SOURCES)
    # make lists
    separate_arguments(STM32CUBEMX_SOURCES)
    # fix pathes
    list(TRANSFORM STM32CUBEMX_SOURCES PREPEND "${CUBEMX_DIR}/")
    set(STM32CUBEMX_SOURCES ${STM32CUBEMX_SOURCES} PARENT_SCOPE)

    # export headers -------------------------------
    MakeFileVariableGrabber(${CMAKE_CURRENT_SOURCE_DIR}/${CUBEMX_PROJECT_NAME} C_INCLUDES CUBEMX_INCLUDE_DIRECTORIES)
    # make lists
    separate_arguments(CUBEMX_INCLUDE_DIRECTORIES)
    # fix pathes
    list(TRANSFORM CUBEMX_INCLUDE_DIRECTORIES REPLACE "^-I" "${CUBEMX_DIR}/")
    set(CUBEMX_INCLUDE_DIRECTORIES ${CUBEMX_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endfunction()
# ##############################################################################