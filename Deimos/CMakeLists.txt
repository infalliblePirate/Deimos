# Define the interface library
add_library(_Deimos INTERFACE)

# Group source files based on platform
set(COMMON_SOURCES src/Deimos/)

if (UNIX)
    message("The os is linux")
    set(PLATFORM_SOURCES
            src/Platform/Linux/LinuxWindow.cpp
            src/Platform/OpenGL/ImGuiOpenGLRenderer.cpp
            src/Platform/Linux/LinuxInput.cpp
    )
    set(DM_PLATFORM DM_PLATFORM_LINUX)
elseif (WIN32)
    message("The os is Windows")
    set(PLATFORM_SOURCES
            src/Platform/Windows/WindowsWindow.cpp
            src/Platform/OpenGL/ImGuiOpenGLRenderer.cpp
            src/Platform/Windows/WindowsInput.cpp
    )
    set(DM_PLATFORM DM_PLATFORM_WINDOWS)
else()
    message(FATAL_ERROR "No platform specified!")
endif ()

# Create the actual shared library target and link with the interface library
add_library(Deimos ${COMMON_SOURCES} ${PLATFORM_SOURCES})

target_link_libraries(Deimos PRIVATE _Deimos)


find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif ()

# Set default build type to Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

# Add debug-specific configurations
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    add_definitions(-DDEBUG)

    # Path to spdlog CMakeLists.txt
    add_subdirectory(vendor/spdlog)

    # Add spdlog library
    target_compile_options(spdlog PRIVATE -fPIC)
    target_link_libraries(Deimos PUBLIC spdlog::spdlog)
endif ()

# Add release-specific configurations
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
endif ()

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

# Set include directories for GLAD
target_include_directories(Deimos PRIVATE vendor/GLAD/include)

# Add GLAD
add_library(glad OBJECT "vendor/GLAD/src/glad.c")
target_include_directories(glad PRIVATE "vendor/GLAD/include")
target_compile_options(glad PRIVATE -fPIC)
target_link_libraries(Deimos PRIVATE glad)

# Set include directories for IMGUI
target_include_directories(Deimos PRIVATE vendor/imgui)

# Add imgui
set(IMGUI_PATH vendor/imgui)
file(GLOB IMGUI_GLOB
        ${IMGUI_PATH}/imgui.h
        ${IMGUI_PATH}/imgui.cpp
        ${IMGUI_PATH}/imconfig.h
        ${IMGUI_PATH}/imgui_demo.cpp
        ${IMGUI_PATH}/imgui_draw.cpp
        ${IMGUI_PATH}/imgui_internal.h
        ${IMGUI_PATH}/imstb_rectpack.h
        ${IMGUI_PATH}/imstb_textedit.h
        ${IMGUI_PATH}/imstb_truetype.h
        ${IMGUI_PATH}/imgui_tables.cpp
        ${IMGUI_PATH}/imgui_widgets.cpp

        # specific bindings...
        ${IMGUI_PATH}/backends/imgui_impl_glfw.h
        ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.h
        ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp
        ${IMGUI_PATH}/backends/imgui_impl_opengl3_loader.cpp)
add_library(imgui STATIC ${IMGUI_GLOB})
target_include_directories(imgui PUBLIC ${IMGUI_PATH})
target_compile_options(imgui PRIVATE -fPIC)
target_link_libraries(imgui PRIVATE glfw)
target_compile_options(imgui PRIVATE -fPIC)
target_link_libraries(Deimos PRIVATE imgui)

# Add glm
add_subdirectory(vendor/glm)
target_link_libraries(Deimos PRIVATE glm)

target_compile_definitions(Deimos PUBLIC DM_ENABLE_ASSERTS ${DM_PLATFORM} DM_BUILD_DLL
        GLFW_INCLUDE_NONE) # GLFW won't include any GL headers, add GLAD to get the headers

# Set output dirs
set_target_properties(Deimos PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
)


