#include "dmpch.h"
#include "Application.h"
#include "spdlog/sinks/stdout_sinks.h"

#include "GLFW/glfw3.h"

namespace Deimos {
    Application::Application() {
        m_window = std::unique_ptr<Window>(Window::create());
    }

    Application::~Application() {

    }

    void Application::run() {
        std::cout << "something";

        while (m_running) {
            glClearColor(1,1,1,1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_window->onUpdate();
        }
    }
}