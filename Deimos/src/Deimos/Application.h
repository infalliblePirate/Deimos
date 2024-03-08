#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

namespace Deimos {
    class WindowCloseEvent;

    class DM_API Application {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay); // why we used a pointer? and not a reference?
    private:
        bool onWindowClose(WindowCloseEvent &e);
        std::unique_ptr<Window> m_window;

        bool m_running = true;

        LayerStack m_layerStack;
    };

    // tob be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
