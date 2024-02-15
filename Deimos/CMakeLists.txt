# Define the library target
add_library(Deimos SHARED
        src/Tester.cpp
        src/Tester.h
)

# Set include directories for the library
target_include_directories(Deimos PUBLIC src)

# Set output directory for the DLL library
set_target_properties(Deimos PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)