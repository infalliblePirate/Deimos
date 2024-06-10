#include "dmpch.h"
#include "Deimos/Core/Core.h"

#include "Renderer2D.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "RenderCommand.h"

namespace Deimos {
    struct Renderer2DStorage {
        Ref<VertexArray> quadVertexArray;
        Ref<Shader> flatColorShader;
    };
    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        s_data = new Renderer2DStorage();

        s_data->quadVertexArray = Deimos::VertexArray::create();
        float squareVertices[3 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f,};

        Deimos::Ref<Deimos::VertexBuffer> squareVB;
        squareVB = Deimos::VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout(
                {
                        {Deimos::ShaderDataType::Float3, "a_position"},
                });
        s_data->quadVertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};

        Deimos::Ref<Deimos::IndexBuffer> squareIB;
        squareIB = Deimos::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

        s_data->quadVertexArray->setIndexBuffer(squareIB);
        s_data->flatColorShader = Deimos::Shader::create(std::string(ASSETS_DIR) + "/shaders/PlainColor.glsl");
    }

    void Renderer2D::shutdown() {
        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        s_data->flatColorShader->bind();
        std::dynamic_pointer_cast<OpenGLShader>(s_data->flatColorShader)->uploadUniformMat4("u_viewProjection", camera.getViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(s_data->flatColorShader)->uploadUniformMat4("u_transform", glm::mat4{1.f});

    }

    void Renderer2D::endScene() {

    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        drawQuad({ position.x, position.y, 0.f }, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        s_data->flatColorShader->bind();
        std::dynamic_pointer_cast<Deimos::OpenGLShader>(s_data->flatColorShader)->uploadUniformFloat4("u_color", color);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }
}
