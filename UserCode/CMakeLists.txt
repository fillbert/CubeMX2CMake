# include autoconfig to all files
add_compile_options(-include ${AUTOCONF_H})

# include directories
add_subdirectory(Drivers)
add_subdirectory(Logger)

# include directories based on config
if (CONFIG_TEST_APP_DEFINE_FEATURE)
    add_subdirectory(SomeModule)
endif()

# include local sources
target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        userSystemInit.c
)

# include local headers
target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# defone compile options
target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE
        -Wall
        $<$<BOOL:${CONFIG_TEST_APP_DEBUG}>:-g -ggdb -Og>
        $<$<BOOL:${CONFIG_TEST_APP_RELEASE}>:-g -Os>
)

# add compile definitions
target_compile_definitions(${CMAKE_PROJECT_NAME}
    PRIVATE
        $<$<BOOL:${CONFIG_TEST_APP_DEFINE_FEATURE}>:USE_DEFINE_FEATURE>
)

