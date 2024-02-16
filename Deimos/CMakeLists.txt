
# Define the library target
add_library(Deimos SHARED
        src/Deimos/Application.h
        src/Deimos/Application.cpp
        src/Deimos/Core.h
        src/Deimos/EntryPoint.h
)

# Set include directories for the library
target_include_directories(Deimos PUBLIC src)

# Set output directory for the DLL library
set_target_properties(Deimos PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Set the DM_PLATFORM_WINDOWS and DM_BUILD_DLL macro
target_compile_definitions(Deimos PRIVATE DM_PLATFORM_WINDOWS DM_BUILD_DLL)

