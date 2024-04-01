#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

struct GLFWwindow;
namespace Deimos {

    class GraphicsContext {
    public:
        virtual void init();
        virtual void swapBuffers();
    };
}

#endif //GRAPHICSCONTEXT_H
