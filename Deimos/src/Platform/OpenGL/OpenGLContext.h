#ifndef OPENGLCONTEXT_H
#define OPENGLCONTEXT_H

#include "Deimos/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Deimos {

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void init() override;
        virtual void swapBuffers() override;
    private:
        GLFWwindow* m_windowHandle;
    };
}


#endif //OPENGLCONTEXT_H
