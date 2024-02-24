#ifndef ENGINE_WINDOWSWINDOW_H
#define ENGINE_WINDOWSWINDOW_H

#include "Deimos/Window.h"
#include <GLFW/glfw3.h>

namespace Deimos {

    class WindowsWindow : public Window {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void onUpdate() override;

        inline unsigned int getWidth() const override { return m_data.width; }
        inline unsigned int getHeight() const override { return m_data.height; }

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
        GLFWwindow* m_window; ///// why here?????????

        struct WindowData {
            std::string title;
            unsigned int width, height;
            bool vSync;

            eventCallbackFn eventCallback;
        };
        WindowData m_data;
    };
}

#endif //ENGINE_WINDOWSWINDOW_H
