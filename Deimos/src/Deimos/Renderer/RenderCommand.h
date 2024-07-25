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

        inline static void drawIndexed(const Ref<VertexArray>& vertexArray) {
            s_rendererAPI->drawIndexed(vertexArray);
        }

        inline static void drawLine(const Ref<VertexArray>& vertexArray, float thickness = 3.f) {
            s_rendererAPI->drawLine(vertexArray, thickness);
        }

        inline static void init() {
            s_rendererAPI->init();
        }

        inline static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_rendererAPI->setViewport(x, y, width, height);
        }
    private:
        static Scope<RendererAPI> s_rendererAPI;
    };
}


#endif //ENGINE_RENDERCOMMAND_H
