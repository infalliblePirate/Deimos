#include "dmpch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "spdlog/sinks/stdout_sinks.h"

#include "GLFW/glfw3.h"


namespace Deimos {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::create());
        m_window->setEventCallback(BIND_EVENT_FN(onEvent)); // set onEvent as the callback fun
    }

    Application::~Application() {

    }

    // whenever an even is occurred, it calls this function
    void Application::onEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        DM_CORE_TRACE("{0}", e);
    }


    void Application::run() {
        while (m_running) {
            glClearColor(1, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent &e) {
        m_running = false;
        return true; // everything went great, the fun was handled
    }
}
