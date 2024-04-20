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

        glGenVertexArrays(1, &m_vertexArray);
        glBindVertexArray(m_vertexArray);

        float vertices[3 * 3]{
                -0.5f, -0.5f, 0.0f,
                0.5f, -0.5f, 0.0f,
                0.0f, 0.5f, 0.0f
        };
        m_vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


        unsigned int indices[3] = {0, 1, 2};

        m_indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint)));

        // input a position
        std::string vertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_position;
            out vec3 v_position; // varying variable

            void main() {
                v_position = a_position;
                gl_Position = vec4(a_position, 1.0);
            }
        )";

        // output a color
        std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;
            in vec3 v_position;

            void main() {
                color = vec4(v_position + 0.5, 1.0);
            }
        )";

        m_shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
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

            m_shader->bind();
            glBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, nullptr);

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
