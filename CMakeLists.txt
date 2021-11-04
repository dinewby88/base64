cmake_minimum_required(VERSION 3.0.0)
project(base64 VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

# input files
set(INPUT_SOURCE_FILES
    ./main.c
    ./mbedtls/library/base64.c
)

# include directories
set(INCLUDE_DIRECTORIES
    ./mbedtls/include
)

# include(CMakePrintHelpers)
# cmake_print_variables(INPUT_SOURCE_FILES)
# message(STATUS "TEST ${CMAKE_CURRENT_LIST_DIR}")

add_executable(base64 ${INPUT_SOURCE_FILES})
target_include_directories(base64 PRIVATE ${INCLUDE_DIRECTORIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
