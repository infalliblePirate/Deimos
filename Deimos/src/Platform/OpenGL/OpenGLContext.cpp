#include "dmpch.h"

#include "OpenGLContext.h"

#include <GLAD/include/glad/glad.h>
#include "GLFW/include/GLFW/glfw3.h"

namespace Deimos {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_windowHandle(windowHandle) {
        DM_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::init() {
        DM_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        DM_CORE_ASSERT(status, "Failed to initialize Glad!");

        DM_CORE_INFO("OpenGL Info:");
        DM_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        DM_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDER));
        DM_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::swapBuffers() {
        DM_PROFILE_FUNCTION();
        
        glfwSwapBuffers(m_windowHandle);
    }
}
