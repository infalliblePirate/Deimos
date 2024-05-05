if (UNIX)
    set(DM_PLATFORM DM_PLATFORM_LINUX)
elseif (WIN32)
    set(DM_PLATFORM DM_PLATFORM_WINDOWS)
endif ()

# Define the executable target
add_executable(Sandbox src/SandboxApp.cpp)

# Set include directories for the executable
target_include_directories(Sandbox PRIVATE src)

# Link the Deimos library to the Sandbox executable
target_link_libraries(Sandbox PRIVATE Deimos)

# Copy DLLs to the output directory
add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Deimos>
        $<TARGET_FILE_DIR:Sandbox>
)

target_compile_definitions(Sandbox PRIVATE ${DM_PLATFORM})

# Enable c++ exception handling
target_compile_options(Sandbox PRIVATE -fexceptions)
