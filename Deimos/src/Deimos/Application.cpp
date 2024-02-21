#include "Application.h"
#include "Log.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "Deimos/Events/MouseEvent.h"

namespace Deimos {
    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::run() {

        MouseScrolledEvent e(5,4);
        if (e.isInCategory(EventCategoryApplication)) {
            DM_TRACE(e.toString());
        }
        if (e.isInCategory(EventCategoryInput)) {
            DM_TRACE(e.toString());
        }

        /*WindowResizeEvent e(1280, 720);
        auto logger = spdlog::stdout_logger_mt("console");
        logger->info(e.toString());*/
        while(true);
    }
}