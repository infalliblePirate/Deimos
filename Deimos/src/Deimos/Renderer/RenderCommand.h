#ifndef ENGINE_RENDERCOMMAND_H
#define ENGINE_RENDERCOMMAND_H

#include "RendererAPI.h"

namespace Deimos {

    class RenderCommand {
    public:
        inline static void setClearColor(const glm::vec4& color) {
            s_rendererAPI->setClearColor(color);
        }

        inline static void clear() {
            s_rendererAPI->clear();
        }

        inline static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
            s_rendererAPI->drawIndexed(vertexArray);
        }

        inline static void init() {
            s_rendererAPI->init();
        }
    private:
        static RendererAPI* s_rendererAPI;
    };
}


#endif //ENGINE_RENDERCOMMAND_H
