#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "Core.h"

namespace DM_API Deimos {
    class Input {
    public:
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;

        inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
        inline static bool isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> getMousePosition() { return s_instance->getMousePositionImpl(); }
        inline static float getMouseX() { return s_instance->getMouseXImpl(); }
        inline static float getMouseY() { return s_instance->getMouseYImpl(); }
    protected:
        Input() = default;
    protected:
        virtual bool isKeyPressedImpl(int keycode) = 0;

        virtual bool isMouseButtonPressedImpl(int button) = 0;
        virtual std::pair <float, float> getMousePositionImpl() = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;
    private:
        static Scope<Input> s_instance;
    };
}


#endif //ENGINE_INPUT_H
