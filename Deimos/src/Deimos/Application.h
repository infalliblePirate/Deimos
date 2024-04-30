#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Deimos/Renderer/VertexArray.h"

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
        std::unique_ptr<Window> m_window;

        bool m_running = true;

        LayerStack m_layerStack;
        ImGuiLayer* m_ImGuiLayer;

        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Shader> m_blueShader;

        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<VertexArray> m_squareVA;

        static Application* s_instance;
    };

    // tob be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
