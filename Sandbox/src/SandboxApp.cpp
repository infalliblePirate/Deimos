#include "Deimos.h"

#include "Deimos/Core/EntryPoint.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Deimos/Renderer/OrthographicCameraController.h"
#include "Sandbox2D.h"

#include <glm/glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Deimos::Layer {
public:
    ExampleLayer() : Layer("Example"),
                     m_cameraController(1280.f/720.f, true) {
        m_vertexArray = Deimos::VertexArray::create();

        float vertices[3 * 7]{
                -0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.4f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.6f, 0.4f, 0.9f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.3f, 0.8f, 0.1f, 1.0f
        };
        Deimos::Ref<Deimos::VertexBuffer> vertexBuffer;
        vertexBuffer = Deimos::VertexBuffer::create(vertices, sizeof(vertices));

        Deimos::BufferLayout layout = {
                {Deimos::ShaderDataType::Float3, "a_position"},
                {Deimos::ShaderDataType::Float4, "a_color"}
        };
        vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};

        Deimos::Ref<Deimos::IndexBuffer> indexBuffer;
        indexBuffer = Deimos::IndexBuffer::create(indices, sizeof(indices) / sizeof(u_int));
        m_vertexArray->setIndexBuffer(indexBuffer);

        m_squareVA = Deimos::VertexArray::create();

        float squareVertices[5 * 4] = {
                -0.5f, -0.5f, 0.0f, 0.f, 0.f,
                0.5f, -0.5f, 0.0f, 1.f, 0.f,
                0.5f, 0.5f, 0.0f, 1.f, 1.f,
                -0.5f, 0.5f, 0.0f, 0.f, 1.f
        };

        Deimos::Ref<Deimos::VertexBuffer> squareVB;
        squareVB = Deimos::VertexBuffer::create(squareVertices, sizeof(squareVertices));
        squareVB->setLayout({
                                    {Deimos::ShaderDataType::Float3, "a_position"},
                                    {Deimos::ShaderDataType::Float2, "a_texCoord"}
                            });
        m_squareVA->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        Deimos::Ref<Deimos::IndexBuffer> squareIB;
        squareIB = Deimos::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));
        m_squareVA->setIndexBuffer(squareIB);

        // input a position
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            out vec3 v_position; // varying variable
            out vec4 v_color;

            void main() {
                v_position = a_position;
                v_color = a_color;
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

        // output a color
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            uniform vec4 u_color;

            void main() {
                color = u_color;
                color = v_color;
            }
        )";

        m_shader = Deimos::Shader::create("vertexPosColor", vertexSrc, fragmentSrc);

        std::string plainColorVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() {
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

        std::string plainColorFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;

            uniform vec4 u_color;

            void main() {
                color = u_color;
            }
        )";
        //plainColorShader.reset(Deimos::Shader::create(plainColorVertexSrc, plainColorFragmentSrc));

        m_TextureShader = Deimos::Shader::create(std::string(ASSETS_DIR) + "/shaders/Texture.glsl");

        m_texture = Deimos::Texture2D::create(std::string(ASSETS_DIR) + "/textures/go.jpeg");
        m_texture2 = Deimos::Texture2D::create(std::string(ASSETS_DIR) + "/textures/chessPiece.png");

        std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_TextureShader)->bind();
        std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_TextureShader)->uploadUniformInt("u_texture", 0);
    }

    void onUpdate(Deimos::Timestep timestep) override {
        m_cameraController.onUpdate(timestep);
        

        Deimos::RenderCommand::setClearColor({0.4, 0.2, 0.1, 1});
        Deimos::RenderCommand::clear();


        Deimos::Renderer::beginScene(m_cameraController.getCamera());
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.07f));

        //std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->bind();
        //std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->uploadUniformFloat4("u_color", m_color);

        std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_TextureShader)->bind();

        std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_TextureShader)->uploadUniformInt("u_texture", 0);
        std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_TextureShader)->uploadUniformFloat4("u_color", m_color);

        m_texture->bind();
        Deimos::Renderer::submit(m_TextureShader, m_squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_texture2->bind();
        Deimos::Renderer::submit(m_TextureShader, m_squareVA, glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        Deimos::Renderer::endScene();
    }

    virtual void onImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::ColorEdit4("Square color", (float *) &m_color);
        ImGui::End();
    }

    void onEvent(Deimos::Event &event) override {
        m_cameraController.onEvent(event);
    }

private:
    Deimos::Ref<Deimos::Shader> m_shader;
    Deimos::Ref<Deimos::Shader> m_plainColorShader;
    Deimos::Ref<Deimos::Shader> m_TextureShader;

    Deimos::Ref<Deimos::VertexArray> m_vertexArray;
    Deimos::Ref<Deimos::VertexArray> m_squareVA;

    Deimos::Ref<Deimos::Texture2D> m_texture, m_texture2;

    Deimos::OrthographicCameraController m_cameraController;

    glm::vec4 m_color{1.f, 1.f, 1.0f, 1.0f};
};

class Sandbox : public Deimos::Application {
public:
    Sandbox() {
        pushLayer(new Sandbox2D);
    }

    ~Sandbox() {

    }
};


Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}
