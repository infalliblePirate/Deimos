#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Core.h"
#include "Window.h"

namespace Deimos {

    class DM_API Application {
    public:
        Application();
        virtual ~Application();

        void run();
    private:
        std::unique_ptr<Window> m_window;
        bool m_running = true;
    };

    // tob be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
