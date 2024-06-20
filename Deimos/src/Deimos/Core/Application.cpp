#include "dmpch.h"
#include "Application.h"

#include "Deimos/Events/ApplicationEvent.h"
#include "spdlog/sinks/stdout_sinks.h"

#include "Deimos/Renderer/Renderer.h"

#include "GLFW/glfw3.h"
#include <memory>

namespace Deimos {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application *Application::s_instance = nullptr;

    Application::Application() {
        DM_PROFILE_FUNCTION();

        DM_CORE_ASSERT(!s_instance, "Application already exists!");
        s_instance = this;

        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent)); // set onEvent as the callback fun
        //m_window->setVSync(false);
        Renderer::init();

        m_ImGuiLayer = new ImGuiLayer();
        pushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {
        DM_PROFILE_FUNCTION();
    }

    void Application::pushLayer(Layer *layer) {
        DM_PROFILE_FUNCTION();

        m_layerStack.pushLayer(layer);
    }

    void Application::pushOverlay(Layer *overlay) {
        DM_PROFILE_FUNCTION();

        m_layerStack.pushOverlay(overlay);
    }

    // whenever event occurs, it calls this function
    void Application::onEvent(Event &e) {
        DM_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));

        // if handled an event, terminate (starts from overlays or last layers)
        for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
            (*--it)->onEvent(e);
            if (e.handled)
                break;
        }
    }

    void Application::run() {
        DM_PROFILE_FUNCTION();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        while (m_running) {
            DM_PROFILE_SCOPE("RunLoop");

            if (!m_isMinimized) {
                {
                    DM_PROFILE_SCOPE("LayerStack onUpdate");
                    for (Layer *layer : m_layerStack)
                        layer->onUpdate(deltaTime);
                }
            }
            
            m_ImGuiLayer->begin();
            {
                DM_PROFILE_SCOPE("LayerStack onImGuiRender");
                for (Layer *layer : m_layerStack)
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

    bool Application::onWindowResize(WindowResizeEvent &e) {
        DM_PROFILE_FUNCTION();
        if(e.getWidth() == 0 || e.getHeight() == 0) {
            m_isMinimized = true;
            return false;
        }

        m_isMinimized = false;
        Renderer::onWindowResize(e.getWidth(), e.getHeight());
        return false; // every layer should be aware of this event

    }
}
