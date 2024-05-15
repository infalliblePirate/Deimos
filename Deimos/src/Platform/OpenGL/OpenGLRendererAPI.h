#ifndef ENGINE_OPENGLRENDERERAPI_H
#define ENGINE_OPENGLRENDERERAPI_H

#include "Deimos/Renderer/RendererAPI.h"

namespace Deimos {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        virtual void setClearColor(const glm::vec4& color) override;
        virtual void clear() override;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) override ;

    };
}


#endif //ENGINE_OPENGLRENDERERAPI_H
