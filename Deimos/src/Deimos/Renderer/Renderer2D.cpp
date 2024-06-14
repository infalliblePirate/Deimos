#include "dmpch.h"
#include "Deimos/Core/Core.h"

#include "Renderer2D.h"
#include "RenderCommand.h"

#include "Shader.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/glm/gtc/matrix_transform.hpp>

namespace Deimos {
    struct Renderer2DStorage {
        Ref<VertexArray> quadVertexArray;
        Ref<Shader> flatColorShader;
        Ref<Shader> textureShader;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        s_data = new Renderer2DStorage();

        s_data->quadVertexArray = Deimos::VertexArray::create();
        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.f, 0.f,
                0.5f, -0.5f, 0.0f, 1.f, 0.f,
                0.5f, 0.5f, 0.0f, 1.f, 1.f,
                -0.5f, 0.5f, 0.0f, 0.f, 1.f
        };

        Deimos::Ref<Deimos::VertexBuffer> squareVB;
        squareVB = Deimos::VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout(
                {
                        { Deimos::ShaderDataType::Float3, "a_position" },
                        { Deimos::ShaderDataType::Float2, "a_texCoord" }
                });
        s_data->quadVertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};

        Deimos::Ref<Deimos::IndexBuffer> squareIB;
        squareIB = Deimos::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

        s_data->quadVertexArray->setIndexBuffer(squareIB);
        s_data->flatColorShader = Deimos::Shader::create(std::string(ASSETS_DIR) + "/shaders/PlainColor.glsl");

        s_data->textureShader = Deimos::Shader::create(std::string(ASSETS_DIR) + "/shaders/Texture.glsl");

        s_data->textureShader->bind();
        s_data->textureShader->setInt("u_texture", 0);
    }

    void Renderer2D::shutdown() {
        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        s_data->flatColorShader->bind();
        s_data->flatColorShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());

        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {

    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color) {
        drawQuad({ position.x, position.y, 0.f }, size, color);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color) {
        s_data->flatColorShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->flatColorShader->setMat4("u_transform", transform);
        s_data->flatColorShader->setFloat4("u_color", color);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture> &texture) {
        drawQuad({ position.x, position.y, 0.f }, size, texture);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture> &texture) {
        s_data->textureShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setInt("u_texture", 0);

        texture->bind();

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }
}
