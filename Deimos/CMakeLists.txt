# Group source files based on platform
set(COMMON_SOURCES
        ./config.h

        src/Deimos/Core/Application.cpp
        src/Deimos/Core/EntryPoint.h
        src/Deimos/Core/Layer.cpp
        src/Deimos/Core/LayerStack.cpp
        src/Deimos/Core/Log.cpp
        src/Deimos/ImGui/ImGuiBuild.cpp
        src/Deimos/ImGui/ImGuiLayer.cpp
        src/Deimos/Renderer/OrthographicCamera.cpp
        src/Deimos/Renderer/Renderer.cpp
        src/Deimos/Renderer/RenderCommand.cpp
        src/Deimos/Renderer/RendererAPI.cpp
        src/Deimos/Renderer/Shader.cpp
        src/Deimos/Renderer/Buffer.cpp
        src/Deimos/Renderer/VertexArray.cpp
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLShader.cpp
        vendor/stb_image/stb_image.cpp
        src/Deimos/Renderer/Texture.cpp
        src/Platform/OpenGL/OpenGLTexture2D.cpp
        src/Platform/OpenGL/OpenGLTexture2D.h
        src/Deimos/Renderer/OrthographicCameraController.cpp
        src/Deimos/Renderer/OrthographicCameraController.h
        src/Deimos/Renderer/Renderer2D.cpp
        src/Deimos/Renderer/Renderer2D.h
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-msse2 -msse3)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/arch:SSE2)
endif()

# Apply compile options to stb_image.cpp
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_BUILD_TYPE MATCHES "Debug")
    set_source_files_properties(vendor/stb_image/stb_image.cpp PROPERTIES COMPILE_OPTIONS "-O2")
endif()

# Platform-specific source files
if (UNIX)
    message("The os is linux")
    list(APPEND PLATFORM_SOURCES
            src/Platform/Linux/LinuxWindow.cpp
            src/Platform/Linux/LinuxInput.cpp
    )
    set(DM_PLATFORM DM_PLATFORM_LINUX)
elseif (WIN32)
    message("The os is Windows")
    list(APPEND PLATFORM_SOURCES
            src/Platform/Windows/WindowsWindow.cpp
            src/Platform/Windows/WindowsInput.cpp
    )
    set(DM_PLATFORM DM_PLATFORM_WINDOWS)
else()
    message(FATAL_ERROR "No platform specified!")
endif ()

# Add Deimos library
add_library(Deimos STATIC ${COMMON_SOURCES} ${PLATFORM_SOURCES})

#set(CMAKE_BUILD_TYPE "Release")
# Set default build type to Debug
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

# Add debug-specific configurations
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")
    target_compile_definitions(Deimos PRIVATE DM_ENABLE_ASSERTS)
endif ()

# Add release-specific configurations
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
    target_compile_definitions(Deimos PRIVATE DM_RELEASE_BUILD)
endif ()

# Enable precompiled header for source files
target_precompile_headers(Deimos PRIVATE "src/dmpch.h")

# Set include directories for the library
target_include_directories(Deimos PUBLIC src)
target_include_directories(Deimos PUBLIC vendor)

# Path to spdlog CMakeLists.txt
add_subdirectory(vendor/spdlog)

# Add spdlog library
target_link_libraries(Deimos PUBLIC spdlog::spdlog)

# glfw disable the build for tests, examples, documentation:
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add GLFW
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
target_include_directories(imgui PRIVATE ${IMGUI_PATH})
target_link_libraries(imgui PRIVATE glfw)
target_link_libraries(Deimos PUBLIC imgui)

# Add glm
add_subdirectory(vendor/glm)
target_link_libraries(Deimos PRIVATE glm)

# Add dummy Cmake for imgui (to enable navigation through its functions)
add_subdirectory(vendor/dummyCmake)

target_compile_definitions(Deimos PUBLIC ${DM_PLATFORM} DM_BUILD_DLL
        GLFW_INCLUDE_NONE) # GLFW won't include any GL headers, add GLAD to get the headers

# Set output directories
set_target_properties(Deimos PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${outputdir}/Deimos"
)

# Use configure_file to generate config.h with directory variables
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)

# Add the binary directory to the include path so that the generated config.h can be found
include_directories(${CMAKE_CURRENT_BINARY_DIR})