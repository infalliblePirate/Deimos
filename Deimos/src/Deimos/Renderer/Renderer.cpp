#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Deimos {

    Scope<Renderer::SceneData> Renderer::s_sceneData = createScope<Renderer::SceneData>();

    void Renderer::onWindowResize(uint32_t width, uint32_t height) {
        RenderCommand::setViewport(0, 0, width, height);
    }

    void Renderer::beginScene(OrthographicCamera camera) {
        s_sceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
    }

    void Renderer::endScene() {

    }

    void Renderer::submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray,
                          const glm::mat4& transform) {
        shader->bind();
        shader->setMat4("u_viewProjection", s_sceneData->viewProjectionMatrix);
        shader->setMat4("u_transform", transform);

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

    void Renderer::init() {
        DM_PROFILE_FUNCTION();
        
        RenderCommand::init();
    }
}

