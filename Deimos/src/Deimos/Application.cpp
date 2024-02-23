#include "dmpch.h"
#include "Application.h"
#include "Log.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "Deimos/Events/KeyEvent.h"

namespace Deimos {
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::run() {

        KeyReleasedEvent e(5);
        if (e.isInCategory(EventCategoryApplication)) {
            DM_TRACE(e.toString());
        }
        if (e.isInCategory(EventCategoryInput)) {
            DM_TRACE(e.toString());
        }

        while(true);
    }
}