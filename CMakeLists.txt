set(CMAKE_VERBOSE_MAKEFILE ON)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

cmake_minimum_required(VERSION 3.20)
project(Engine)

# With this no error like the procedure entry point _zst28__throw_bad could not be located in the dynamic link library
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_subdirectory(Deimos)
add_subdirectory(Sandbox)