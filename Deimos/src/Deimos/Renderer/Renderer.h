#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

namespace Deimos {
    enum class RendererAPI {
        None = 0, OpenGL = 1
    };

    class Renderer {
    public:
        inline static RendererAPI getAPI () { return s_rendererAPI; }
    private:
        static RendererAPI s_rendererAPI;
    };

}



#endif //ENGINE_RENDERER_H
