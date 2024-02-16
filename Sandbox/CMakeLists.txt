# Define the executable target
add_executable(Sandbox src/SandboxApp.cpp)

# Link the Deimos library to the Sandbox executable
target_link_libraries(Sandbox PRIVATE Deimos)

# Copy DLLs to the output directory
add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Deimos>
        $<TARGET_FILE_DIR:Sandbox>
)

# Set the DM_PLATFORM_WINDOWS
target_compile_definitions(Sandbox PRIVATE DM_PLATFORM_WINDOWS)