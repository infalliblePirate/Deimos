#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Deimos {

    class Renderer {
    public:
        static void beginScene(OrthographicCamera camera);
        static void endScene();
        static void submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray>& vertexArray,
                           const glm::mat4& transform = glm::mat4(1.0f));

        static void init();
        static void onWindowResize(uint32_t width, uint32_t height);
        inline static RendererAPI::API getAPI () { return RendererAPI::getAPI(); }
    private:
        struct SceneData {
            glm::mat4 viewProjectionMatrix;
        };
        static Scope<SceneData> s_sceneData;
    };

}



#endif //ENGINE_RENDERER_H
