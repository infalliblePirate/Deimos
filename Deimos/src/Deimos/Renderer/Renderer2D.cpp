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
        Ref<VertexArray> lineVertexArray;
        Ref<VertexArray> quadVertexArray;
        Ref<VertexArray> triangleVertexArray;
        Ref<VertexArray> circleVertexArray;
        Ref<VertexArray> polygonVertexArray;
        
        Ref<Shader> textureShader;
        Ref<Shader> plainColorShader;
        Ref<Texture2D> whiteTexture;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::init() {
        DM_PROFILE_FUNCTION();

        s_data = new Renderer2DStorage();

        // LINE
        s_data->lineVertexArray = VertexArray::create();
        float lineVertices[2 * 3]{
            0.0f, 0.0f, 0.0f, 
            1.f, 0.0f, 0.0f,
        };

        Ref<VertexBuffer> lineVB;
        lineVB = VertexBuffer::create(lineVertices, sizeof(lineVertices));
        lineVB->setLayout(
            {
                { ShaderDataType::Float3, "a_position" }
            }
        );

        s_data->lineVertexArray->addVertexBuffer(lineVB);

        unsigned int lineindices[2] = { 0, 1 };

        Ref<IndexBuffer> lineIB;
        lineIB = IndexBuffer::create(lineindices, sizeof(lineindices) / sizeof(unsigned int));

        s_data->lineVertexArray->setIndexBuffer(lineIB);

        s_data->plainColorShader = Shader::create(std::string(ASSETS_DIR) + "/shaders/PlainColor.glsl");

        // QUAD
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


        // TRIANGLE:
        s_data->triangleVertexArray = VertexArray::create();
        float triangleVertices[3 * 3]{
            -0.5f, -0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        Ref<VertexBuffer> triangleVB;
        triangleVB = VertexBuffer::create(triangleVertices, sizeof(triangleVertices));
        triangleVB->setLayout(
            {
                { ShaderDataType::Float3, "a_position" }
            }
        );

        s_data->triangleVertexArray->addVertexBuffer(triangleVB);

        unsigned int triangleindices[3] = { 0, 1, 2 };

        Ref<IndexBuffer> triangleIB;
        triangleIB = IndexBuffer::create(triangleindices, sizeof(triangleindices) / sizeof(unsigned int));

        s_data->triangleVertexArray->setIndexBuffer(triangleIB);

        s_data->plainColorShader = Shader::create(std::string(ASSETS_DIR) + "/shaders/PlainColor.glsl");


        // CIRCLE
        // TODO change from predefined behaviour
        int vCount = 32; // count of "angles" in a circle
        float angle = 360.f / vCount;
        int triangleCount = vCount - 2;

        std::vector<glm::vec3> temp;

        // positions
        for (size_t i = 0; i < vCount; ++i) {
            float x = cos(glm::radians(angle * i));
            float y = sin(glm::radians(angle * i));
            float z = 0.f;

            temp.push_back(glm::vec3(x, y, z));
        }

        s_data->circleVertexArray = VertexArray::create();

        float circleVertices[3 * vCount]; // create circle vertices array
        for (size_t i = 0, j = 0; i < vCount; ++i) {
            circleVertices[j++] = temp[i].x;
            circleVertices[j++] = temp[i].y;
            circleVertices[j++] = temp[i].z;
        }

        Ref<VertexBuffer> circleVB;
        circleVB = VertexBuffer::create(circleVertices, sizeof(circleVertices));
        circleVB->setLayout(
            {
                { ShaderDataType::Float3, "a_position"}
            }
        );

        s_data->circleVertexArray->addVertexBuffer(circleVB);

       unsigned int circleIndices[3 * triangleCount];
        for (size_t i = 0, j = 0; i < triangleCount; ++i) {
            circleIndices[j++] = 0; // origin
            circleIndices[j++] = i + 1;
            circleIndices[j++] = i + 2;
        }

        Ref<IndexBuffer> circleIB;
        circleIB = IndexBuffer::create(circleIndices, sizeof(circleIndices) / sizeof(unsigned int));

        s_data->circleVertexArray->setIndexBuffer(circleIB);
    }

    void Renderer2D::shutdown() {
        DM_PROFILE_FUNCTION();

        delete s_data;
    }

    void Renderer2D::beginScene(const OrthographicCamera &camera) {
        DM_PROFILE_FUNCTION();

        s_data->textureShader->bind();
        s_data->textureShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());

        s_data->plainColorShader->bind();
        s_data->plainColorShader->setMat4("u_viewProjection", camera.getViewProjectionMatrix());
    }

    void Renderer2D::endScene() {
        DM_PROFILE_FUNCTION();
    }

    void Renderer2D::drawLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        drawLine({ start.x, start.y, 0.f }, { end.x, end.y, 0.f }, thickness, color, tilingFactor, tintColor );
    }

    void Renderer2D::drawLine(const glm::vec3 &start, const glm::vec3 &end, float thickness, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        DM_PROFILE_FUNCTION();

        s_data->plainColorShader->bind();
        glm::vec3 direction = end - start; // direction vector
        float length = glm::length(direction);

        // calculate the angle of rotation in radians
        float angle = glm::atan(direction.y, direction.x);

        // create transformation matrix
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, start); // move origin
        transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
        transform = glm::scale(transform, glm::vec3(length, 1.f, 1.0f)); // strech along the x axis


        s_data->plainColorShader->setMat4("u_transform", transform);
        s_data->plainColorShader->setFloat4("u_color", color * tintColor);

        s_data->lineVertexArray->bind();
        RenderCommand::drawLine(s_data->lineVertexArray, thickness);
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

    void Renderer2D::drawTriangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        drawTriangle({ position.x, position.y, 0}, size, color, tilingFactor, tintColor);
    }

    void Renderer2D::drawTriangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        DM_PROFILE_FUNCTION();

        s_data->plainColorShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f} );
        s_data->plainColorShader->setMat4("u_transform", transform);
        s_data->plainColorShader->setFloat4("u_color", color * tintColor);

        s_data->triangleVertexArray->bind();
        RenderCommand::drawIndexed(s_data->triangleVertexArray);
    }

    /**@param rotation The rotation of the triangle in radians*/
    void Renderer2D::drawRotatedTriangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor, const glm::vec4 &tintColor) {
        drawRotatedTriangle({ position.x, position.y, 0}, size, color, rotation, tilingFactor, tintColor);
    }


    /**@param rotation The rotation of the triangle in radians*/
    void Renderer2D::drawRotatedTriangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor, const glm::vec4 &tintColor) {
        DM_PROFILE_FUNCTION();

        s_data->plainColorShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), rotation, { 0, 0, 1}) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f} );
        s_data->plainColorShader->setMat4("u_transform", transform);
        s_data->plainColorShader->setFloat4("u_color", color * tintColor);

        s_data->triangleVertexArray->bind();
        RenderCommand::drawIndexed(s_data->triangleVertexArray);
    }
    
    void Renderer2D::drawCircle(const glm::vec2 &position, float radius, int vCount, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        drawCircle({ position.x, position.y, 0.f }, radius, vCount, color, tilingFactor, tintColor);
    }

    void Renderer2D::drawCircle(const glm::vec3 &position, float radius, int vCount, const glm::vec4 &color, float tilingFactor, const glm::vec4 &tintColor) {
        DM_PROFILE_FUNCTION();

        s_data->plainColorShader->bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { radius, radius, 1.f} );
        s_data->plainColorShader->setMat4("u_transform", transform);
        s_data->plainColorShader->setFloat4("u_color", color * tintColor);

        s_data->circleVertexArray->bind();
        RenderCommand::drawIndexed(s_data->circleVertexArray);
    }
    

    void Renderer2D::drawPolygon(const glm::vec3 *vertices, int vCount, const glm::vec4 &color, float tilingFactor, const glm::vec4& tintColor) {
        float polygonVertices[vCount * 3];
        int triangleCount = vCount - 2; // the num of triangles that need to be drawn to make up the shape

        s_data->polygonVertexArray = Deimos::VertexArray::create();

        Ref<VertexBuffer> polygonVB; 
        for (size_t i = 0, j = 0; i < vCount; ++i) {
            polygonVertices[j++] = vertices[i].x;
            polygonVertices[j++] = vertices[i].y;
            polygonVertices[j++] = vertices[i].z;
        }

        polygonVB = VertexBuffer::create(polygonVertices, sizeof(polygonVertices));
        polygonVB->setLayout(
                {
                        { ShaderDataType::Float3, "a_position" },
                });
        s_data->polygonVertexArray->addVertexBuffer(polygonVB);

        unsigned int polygonIndices[3 * triangleCount];
        int left = 0;
        int right = vCount - 1;
        int index = 0;

        // filled by alternating between vertices from the left and right ends of the vertex list, progressing towards the middle
        // pattern: 0 1 17
        //         17 1 16
        //          1 2 16
        //         16 2 15
        //          2 3 15 
        //             ...
        //          10 8 9
        while (left < right) {
            polygonIndices[index++] = left;
            polygonIndices[index++] = left + 1;
            polygonIndices[index++] = right;

            if (left + 1 < right - 1) { // fails for odd number of triangles
                polygonIndices[index++] = right;
                polygonIndices[index++] = left + 1;
                polygonIndices[index++] = right - 1;
            }

            left++;
            right--;
        }

        Ref<IndexBuffer> polygonIB;
        polygonIB = IndexBuffer::create(polygonIndices, sizeof(polygonIndices) / sizeof(unsigned int));

        s_data->polygonVertexArray->setIndexBuffer(polygonIB);

        DM_ASSERT(m_wasPropsSetterCalled, "The setPolygonProps() function must be called first.");
        DM_PROFILE_FUNCTION();

        s_data->plainColorShader->bind();

        glm::mat4 transform = glm::mat3(1.f);
        s_data->plainColorShader->setMat4("u_transform", transform);
        s_data->plainColorShader->setFloat4("u_color", color * tintColor);

        s_data->polygonVertexArray->bind();
        RenderCommand::drawIndexed(s_data->polygonVertexArray);
    }
}
