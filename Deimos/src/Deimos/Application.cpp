#include "dmpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "spdlog/sinks/stdout_sinks.h"

#include <glad/glad.h>

#include <memory>

namespace Deimos {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application *Application::s_instance = nullptr;

    Application::Application() {
        DM_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent)); // set onEvent as the callback fun
        m_ImGuiLayer = new ImGuiLayer();
        pushOverlay(m_ImGuiLayer);

        m_vertexArray.reset(VertexArray::create());

        float vertices[3 * 7]{
                -0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.4f, 1.0f,
                0.5f, -0.5f, 0.0f, 0.6f, 0.4f, 0.9f, 1.0f,
                0.0f, 0.5f, 0.0f, 0.3f, 0.8f, 0.1f, 1.0f
        };
        std::shared_ptr<VertexBuffer> vertexBuffer;
        vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        BufferLayout layout = {
                {ShaderDataType::Float3, "a_position"},
                {ShaderDataType::Float4, "a_color"}
        };
        vertexBuffer->setLayout(layout);
        m_vertexArray->addVertexBuffer(vertexBuffer);

        unsigned int indices[3] = {0, 1, 2};

        std::shared_ptr<IndexBuffer> indexBuffer;
        indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(u_int)));
        m_vertexArray->setIndexBuffer(indexBuffer);

        m_squareVA.reset(VertexArray::create());

        float squareVertices[3 * 4] = {
                -0.75f, -0.75f, 0.0f,
                0.75f, -0.75f, 0.0f,
                0.75f, 0.75f, 0.0f,
                -0.75f, 0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));
        squareVB->setLayout({
                                    {ShaderDataType::Float3, "a_position"}
                            });
        m_squareVA->addVertexBuffer(squareVB);

        unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
        m_squareVA->setIndexBuffer(squareIB);

        // input a position
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            layout(location = 1) in vec4 a_color;

            out vec3 v_position; // varying variable
            out vec4 v_color;

            void main() {
                v_position = a_position;
                v_color = a_color;
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        // output a color
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_position;
            in vec4 v_color;

            void main() {
                color = vec4(v_position + 0.5, 1.0);
                color = v_color;
            }
        )";

        m_shader.reset(new Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;

            void main() {
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        // output a color
        std::string blueShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            void main() {
                color = vec4(1.0, 1.0, 1.0, 1.0);
            }
        )";

        m_blueShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    Application::~Application() {

    }

    void Application::pushLayer(Layer *layer) {
        m_layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *overlay) {
        m_layerStack.pushOverlay(overlay);
    }

    // whenever an even is occurred, it calls this function
    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        // if handled an event, terminate (starts from overlays or last layers)
        for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.handled)
                break;
        }
    }


    void Application::run() {
        while (m_running) {
            glClearColor(0.4, 0.2, 0.1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_blueShader->bind();
            m_squareVA->bind();
            glDrawElements(GL_TRIANGLES, m_squareVA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

            m_shader->bind();
            m_vertexArray->bind();
            glDrawElements(GL_TRIANGLES, m_vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer *layer: m_layerStack)
                layer->onUpdate();

            m_ImGuiLayer->begin();
            for (Layer *layer: m_layerStack) {
                layer->onImGuiRender();
            }
            m_ImGuiLayer->end();

            m_window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent &e) {
        m_running = false;
        return true; // everything went great, the fun was handled
    }
}
