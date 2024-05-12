#include <Deimos/ImGui/ImGuiLayer.h>

#include "iostream"
#include "Deimos.h"
#include "glm/glm/ext/matrix_transform.hpp"

class ExampleLayer : public Deimos::Layer {
public:
    ExampleLayer() : Layer("Example"),
                     m_camera(-1.6f, 1.6f, -0.9f, 0.9f), m_cameraRotation(0.f) {
        m_vertexArray.reset(Deimos::VertexArray::create());

        float vertices[3 * 7]{
                -0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.4f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.6f, 0.4f, 0.9f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.3f, 0.8f, 0.1f, 1.0f
        };
        std::shared_ptr<Deimos::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Deimos::VertexBuffer::create(vertices, sizeof(vertices)));

        Deimos::BufferLayout layout = {
                {Deimos::ShaderDataType::Float3, "a_position"},
                {Deimos::ShaderDataType::Float4, "a_color"}
        };
        vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};

        std::shared_ptr<Deimos::IndexBuffer> indexBuffer;
        indexBuffer.reset(Deimos::IndexBuffer::create(indices, sizeof(indices) / sizeof(u_int)));
        m_vertexArray->setIndexBuffer(indexBuffer);

        m_squareVA.reset(Deimos::VertexArray::create());

        float squareVertices[3 * 4] = {
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.5f, 0.5f, 0.0f,
                -0.5f, 0.5f, 0.0f
        };

        std::shared_ptr<Deimos::VertexBuffer> squareVB;
        squareVB.reset(Deimos::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
        squareVB->setLayout({
                                    {Deimos::ShaderDataType::Float3, "a_position"}
                            });
        m_squareVA->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Deimos::IndexBuffer> squareIB;
        squareIB.reset(Deimos::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
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

        m_shader.reset(new Deimos::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;

            uniform mat4 u_viewProjection;
            uniform mat4 u_transform;

            void main() {
                gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
            }
        )";

        // output a color
        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            uniform vec4 u_color;

            void main() {
                color = u_color;
            }
        )";

        m_blueShader.reset(new Deimos::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    void onUpdate(Deimos::Timestep timestep) override {
        std::cout << timestep << std::endl;
        {
            if (Deimos::Input::isKeyPressed(DM_KEY_LEFT)) {
                m_cameraPosition.x -= m_cameraMoveSpeed * timestep;
            } else if (Deimos::Input::isKeyPressed(DM_KEY_RIGHT)) {
                m_cameraPosition.x += m_cameraMoveSpeed * timestep;
            }

            if (Deimos::Input::isKeyPressed(DM_KEY_UP)) {
                m_cameraPosition.y += m_cameraMoveSpeed * timestep;
            } else if (Deimos::Input::isKeyPressed(DM_KEY_DOWN)) {
                m_cameraPosition.y -= m_cameraMoveSpeed * timestep;
            }

            if (Deimos::Input::isKeyPressed(DM_KEY_A)) {
                m_cameraRotation += m_cameraRotationSpeed * timestep;
            } else if (Deimos::Input::isKeyPressed(DM_KEY_D)) {
                m_cameraRotation -= m_cameraRotationSpeed * timestep;
            }
        }

        Deimos::RenderCommand::setClearColor({0.4, 0.2, 0.1, 1});
        Deimos::RenderCommand::clear();

        m_camera.setPosition(m_cameraPosition);
        m_camera.setRotation(m_cameraRotation);

        Deimos::Renderer::beginScene(m_camera);
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.07f));

        static glm::vec4 black = {0, 0, 0, 1};
        static glm::vec4 white = {1, 1, 1, 1};

        glm::vec4 currentColor;
        int i = 0;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (i % 2 == 0) {
                    currentColor = black;
                } else {
                    currentColor = white;
                }
                glm::vec3 pos(x * 0.073f, y * 0.073f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Deimos::Renderer::submit(m_blueShader, m_squareVA, transform, currentColor);
                i++;
            }
            i++;
        }
        //Deimos::Renderer::submit(m_shader, m_vertexArray);
        Deimos::Renderer::endScene();
    }

    virtual void onImGuiRender() override {

    }

    void onEvent(Deimos::Event &event) override {

    }

    std::vector<std::vector<int>> readTextFile(const std::string &filename, int rows, int cols) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Unable to open file " << filename << std::endl;
            return {};
        }
        std::vector<std::vector<int>> matrix;

        if (file.is_open()) {
            matrix.resize(rows, std::vector<int>(cols));

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    char bit;
                    file >> bit;
                    matrix[i][j] = bit - '0';
                }
            }

            file.close();
        }

        return matrix;
    }


private:
    std::shared_ptr<Deimos::Shader> m_shader;
    std::shared_ptr<Deimos::Shader> m_blueShader;

    std::shared_ptr<Deimos::VertexArray> m_vertexArray;
    std::shared_ptr<Deimos::VertexArray> m_squareVA;

    Deimos::OrthographicCamera m_camera;
    glm::vec3 m_cameraPosition{0.f};

    float m_cameraMoveSpeed = 0.2f;
    float m_cameraRotation = 0.f;
    float m_cameraRotationSpeed = 10.f;
};

class Sandbox : public Deimos::Application {
public:
    Sandbox() {
        pushLayer(new ExampleLayer);
    }

    ~Sandbox() {

    }
};


Deimos::Application *Deimos::createApplication() {
    return new Sandbox();
}
