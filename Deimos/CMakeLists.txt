# Define the library target
add_library(Deimos SHARED)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif()

# Set default build type to Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE  "Debug")
endif ()

# Add debug-specific configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    add_definitions(-DDEBUG)

    # Path to spdlog CMakeLists.txt
    add_subdirectory(vendor/spdlog)

    # Add spdlog library
    target_link_libraries(Deimos PUBLIC spdlog::spdlog)
endif()

# Add release-specific configurations
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
endif()

# Enable Unity Builds
file(GLOB_RECURSE ENGINE_SOURCE_FILES "src/*.cpp")
target_sources(Deimos PRIVATE ${ENGINE_SOURCE_FILES})

# Enable precompiled header for source files
target_precompile_headers(Deimos PRIVATE "src/dmpch.h")

# Set include directories for the library
target_include_directories(Deimos PUBLIC src)

# glfw disable the build for tests, examples, documentation:
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add the root directory of the GLFW
add_subdirectory(vendor/GLFW)

# Add glfw library
target_link_libraries(Deimos PRIVATE glfw)

# Add OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(Deimos PRIVATE OpenGL::GL)

target_compile_definitions(Deimos PRIVATE DM_PLATFORM_WINDOWS DM_BUILD_DLL)

# Set output dirs
set_target_properties(Deimos PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
)


