# Define the library target
add_library(Deimos SHARED
        src/Deimos/Application.h
        src/Deimos/Application.cpp
        src/Deimos/Core.h
        src/Deimos/Log.h
        src/Deimos/Log.cpp
        src/Deimos/EntryPoint.h
        src/Deimos/Events
)

# Enable Unity Builds
file(GLOB_RECURSE ENGINE_SOURCE_FILES "src/*.cpp")
target_sources(Deimos PRIVATE ${ENGINE_SOURCE_FILES})

# Enable precompiled header for source files
target_precompile_headers(Deimos PRIVATE "src/dmpch.h")

# Set include directories for the library
target_include_directories(Deimos PUBLIC src)

# Add any other configurations (compiler flags, etc.) as needed

# Path to spdlog CMakeLists.txt
add_subdirectory(vendor/spdlog)

# Add spdlog library
target_link_libraries(Deimos PUBLIC spdlog::spdlog)

target_compile_definitions(Deimos PRIVATE DM_PLATFORM_WINDOWS DM_BUILD_DLL)

