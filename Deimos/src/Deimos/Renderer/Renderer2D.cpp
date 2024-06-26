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
        Ref<Shader> textureShader;
        Ref<Texture2D> whiteTexture;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        DM_PROFILE_FUNCTION();

        s_data = new Renderer2DStorage();

        s_data->quadVertexArray = Deimos::VertexArray::create();
        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.f, 0.f,
                0.5f, -0.5f, 0.0f, 1.f, 0.f,
                0.5f, 0.5f, 0.0f, 1.f, 1.f,
                -0.5f, 0.5f, 0.0f, 0.f, 1.f
        };

        Ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout(
                {
                        { ShaderDataType::Float3, "a_position" },
                        { ShaderDataType::Float2, "a_texCoord" }
                });
        s_data->quadVertexArray->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};

        Ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

        s_data->quadVertexArray->setIndexBuffer(squareIB);
        s_data->textureShader = Shader::create(std::string(ASSETS_DIR) + "/shaders/Texture.glsl");

        s_data->whiteTexture = Texture2D::create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->whiteTexture->setData(&whiteTextureData, sizeof(uint32_t));

        s_data->textureShader->bind();
        s_data->textureShader->setInt("u_texture", 0);
    }

    void Renderer2D::shutdown() {
        DM_PROFILE_FUNCTION();

        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        DM_PROFILE_FUNCTION();

        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {
        DM_PROFILE_FUNCTION();
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor, const glm::vec4& tintColor) {
        drawQuad({ position.x, position.y, 0.f }, size, color, tilingFactor, tintColor);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor, const glm::vec4& tintColor) {
        DM_PROFILE_FUNCTION();

        s_data->textureShader->bind();
        s_data->whiteTexture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", color * tintColor);
        s_data->textureShader->setInt("u_texture", 0);
        s_data->textureShader->setFloat("u_tilingFactor", tilingFactor);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    /**@param rotation The rotation of the quad in radians*/
    void Renderer2D::drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        drawRotatedQuad({ position.x, position.y, 0 }, size, color, rotation, tilingFactor, tintColor);
    }

    /**@param rotation The rotation of the quad in radians*/
    void Renderer2D::drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        DM_PROFILE_FUNCTION()

        s_data->textureShader->bind();
        s_data->whiteTexture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), rotation, { 0, 0, 1}) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", color * tintColor);
        s_data->textureShader->setInt("u_texture", 0);
        s_data->textureShader->setFloat("u_tilingFactor", tilingFactor);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    void Renderer2D::drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture> &texture, float tilingFactor, const glm::vec4& tintColor) {
        drawQuad({ position.x, position.y, 0.f }, size, texture, tilingFactor, tintColor);
    }

    void Renderer2D::drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture> &texture, float tilingFactor, const glm::vec4& tintColor) {
        DM_PROFILE_FUNCTION();
        
        s_data->textureShader->bind();
        texture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", tintColor);
        s_data->textureShader->setInt("u_texture", 0);
        s_data->textureShader->setFloat("u_tilingFactor", tilingFactor);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }

    /**@param rotation The rotation of the quad in radians*/
    void Renderer2D::drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture> &texture, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        drawRotatedQuad({ position.x, position.y, 0.f }, size, texture, rotation, tilingFactor, tintColor);
    }

    /**@param rotation The rotation of the quad in radians*/
    void Renderer2D::drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture> &texture, float rotation, float tilingFactor, const glm::vec4& tintColor) {
        DM_PROFILE_FUNCTION()

        s_data->textureShader->bind();
        texture->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), rotation, { 0, 0, 1}) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
        s_data->textureShader->setMat4("u_transform", transform);
        s_data->textureShader->setFloat4("u_color", tintColor);
        s_data->textureShader->setInt("u_texture", 0);
        s_data->textureShader->setFloat("u_tilingFactor", tilingFactor);

        s_data->quadVertexArray->bind();
        RenderCommand::drawIndexed(s_data->quadVertexArray);
    }
}
