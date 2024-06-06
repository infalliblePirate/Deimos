#ifndef ENGINE_WINDOWSINPUT_H
#define ENGINE_WINDOWSINPUT_H

#include "Deimos/Core/Input.h"

namespace Deimos {

    class WindowsInput : public Input {
    protected:
        virtual bool isKeyPressedImpl(int keycode) override;
        virtual bool isMouseButtonPressedImpl(int button) override;
        virtual std::pair <float, float> getMousePositionImpl() override;
        virtual float getMouseXImpl() override;
        virtual float getMouseYImpl() override;
    };
}


#endif //ENGINE_WINDOWSINPUT_H
