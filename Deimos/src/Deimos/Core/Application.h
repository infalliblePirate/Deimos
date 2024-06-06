#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Deimos/ImGui/ImGuiLayer.h"
#include "Deimos/Renderer/Shader.h"
#include "Deimos/Renderer/Buffer.h"
#include "Deimos/Renderer/VertexArray.h"
#include "Deimos/Renderer/OrthographicCamera.h"
#include "Deimos/Core/Timestep.h"

namespace Deimos {

    class DM_API Application {
    public:
        Application();
        virtual ~Application();

        void run();

        void onEvent(Event& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        inline Window& getWindow() { return *m_window; }
        inline static Application& get() { return *s_instance; }
    private:
        bool onWindowClose(WindowCloseEvent &e);
        bool onWindowResize(WindowResizeEvent& e);
        std::unique_ptr<Window> m_window;

        bool m_running = true;

        LayerStack m_layerStack;
        ImGuiLayer* m_ImGuiLayer;

        Timestep m_lastFrameTime = 0.f;
    private:
        static Application* s_instance;
        bool m_isMinimized = false;
    };

    // tob be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
