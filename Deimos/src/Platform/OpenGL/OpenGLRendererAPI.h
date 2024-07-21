#ifndef ENGINE_OPENGLRENDERERAPI_H
#define ENGINE_OPENGLRENDERERAPI_H

#include "Deimos/Renderer/RendererAPI.h"

namespace Deimos {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void init() override;

        virtual void setClearColor(const glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void drawLine(const Ref<VertexArray>& vertexArray, float thickness) override;

        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    };
}


#endif //ENGINE_OPENGLRENDERERAPI_H
