set(CMAKE_VERBOSE_MAKEFILE ON)

cmake_minimum_required(VERSION 3.20)
project(Engine)

# Define directory variables
set(PROJECT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ASSETS_DIR "\"${PROJECT_BASE_DIR}/Sandbox/assets\"")
set(DEBUG_DIR "\"${PROJECT_BASE_DIR}/Deimos/src/Deimos/Debug\"")

# Use configure_file to generate config.h with directory variables
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

# Add the binary directory to the include path so that the generated config.h can be found
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# With this no error like the procedure entry point _zst28__throw_bad could not be located in the dynamic link library
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_subdirectory(Deimos)
add_subdirectory(Sandbox)