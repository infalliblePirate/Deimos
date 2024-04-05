#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace Deimos {

    class GraphicsContext {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };
}

#endif //GRAPHICSCONTEXT_H
