#ifndef ENGINE_LINUXWINDOW_H
#define ENGINE_LINUXWINDOW_H

#include "Deimos/Core/Window.h"
#include "Deimos/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Deimos {

    class LinuxWindow : public Window {
    public:
        LinuxWindow(const WindowProps& props);
        virtual ~LinuxWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return m_data.width; }
        inline unsigned int getHeight() const override { return m_data.height; }
        inline void* getNativeWindow() const override { return m_window; }

        // Window attributes
        inline void setEventCallback(const eventCallbackFn &callback) override {
            m_data.eventCallback = callback;
        }

        void setVSync(bool enabled) override;
        bool isVSync() const override;
    private:
        virtual void init(const WindowProps& props);
        virtual void shutdown();

    private:
        GLFWwindow* m_window; // a base window, the whole WindowsWindow : Window is an overall window wtih extra custom data
        Scope<GraphicsContext> m_context;

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync; // is vertical synchronization set

            eventCallbackFn eventCallback;
        };
        WindowData m_data;
    };
}


#endif //ENGINE_LINUXWINDOW_H
