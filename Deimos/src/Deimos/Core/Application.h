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

extern int main(int argc, char** argv);

namespace Deimos {

    class DM_API Application {
    public:
        Application();
        virtual ~Application();

        void onEvent(Event& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);

        inline Window& getWindow() { return *m_window; }
        inline static Application& get() { return *s_instance; }
    private:
        friend int ::main(int argc, char** argv);
        void run();

        bool onWindowClose(WindowCloseEvent &e);
        bool onWindowResize(WindowResizeEvent& e);
    private:
        std::unique_ptr<Window> m_window;

        LayerStack m_layerStack;
        ImGuiLayer* m_ImGuiLayer;

        Timestep m_lastFrameTime = 0.f;

        bool m_running = true;
        bool m_isMinimized = false;
    private:
        static Application* s_instance;
    };

    // to be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
