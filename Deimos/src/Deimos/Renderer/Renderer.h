#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "RenderCommand.h"

namespace Deimos {

    class Renderer {
    public:
        static void beginScene() {

        }

        static void endScene() {

        }

        static void submit(const std::shared_ptr<VertexArray>& vertexArray) {
            vertexArray->bind();
            RenderCommand::drawIndexed(vertexArray);
        }

        inline static RendererAPI::API getAPI () { return RendererAPI::getAPI(); }
    };

}



#endif //ENGINE_RENDERER_H
