#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "Core.h"
#include "Deimos/Events/Event.h"

namespace Deimos {

    struct WindowProps {
        std::string title;
        unsigned int width;
        unsigned int height;

        WindowProps(const std::string &title = "Deimos Engine", unsigned int width = 1280, unsigned int height = 720)
                : title(title), width(width), height(height) {
        }
    };

    class DM_API Window {
    public:
        // name wrapper as callbackFn, can store a fun which accepts Event&, returns void
        using eventCallbackFn = std::function<void(Event&)>;
        virtual ~Window() {}
        virtual void onUpdate() = 0;

        virtual unsigned int getWidth() const = 0;
        virtual unsigned int getHeight() const = 0;

        // window attributes
        virtual void setEventCallback(const eventCallbackFn& callback) = 0;

        // used to avoid display tearing
        virtual void setVSync(bool enabled) = 0;
        virtual bool isVSync() const = 0;

        // return void pointer to not depend on GLFW library
        virtual void* getNativeWindow() const = 0;

        static Window* create(const WindowProps& props = WindowProps());
    };
}


#endif //ENGINE_WINDOW_H
