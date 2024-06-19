#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Deimos/Core/Layer.h"

#include <Deimos/Events/ApplicationEvent.h>
#include <Deimos/Events/KeyEvent.h>
#include <Deimos/Events/MouseEvent.h>

namespace Deimos {
    class DM_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void onAttach()override;
        virtual void onDetach()override;

        void begin();
        void end();
    private:
        bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool onMouseScrolledEvent(MouseScrolledEvent& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);
        bool onKeyPressedEvent(KeyPressedEvent& e);
        bool onKeyReleasedEvent(KeyReleasedEvent& e);
        bool onKeyTypedEvent(KeyTypedEvent& e);
        bool onWindowResizeEvent(WindowResizeEvent& e);
    private:
        float m_time = 0.0f;
    };
}


#endif //IMGUILAYER_H
