#include "dmpch.h"

#include "OpenGLContext.h"

#include <GLAD/include/glad/glad.h>
#include "GLFW/include/GLFW/glfw3.h"

namespace Deimos {
    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_windowHandle(windowHandle) {
    }

    void OpenGLContext::init() {
        glfwMakeContextCurrent(m_windowHandle);

        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        DM_CORE_ASSERT(status, "Failed to initialize Glad");
    }

    void OpenGLContext::swapBuffers() {
        glfwSwapBuffers(m_windowHandle);
    }
}
