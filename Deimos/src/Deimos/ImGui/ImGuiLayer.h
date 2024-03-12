#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Deimos/Core.h"
#include "Deimos/Layer.h"

namespace Deimos {
    class DM_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void onAttach();
        void onDetach();
        void onUpdate();
        void onEvent(Event& event);
    private:
        float m_time = 0.0f;
    };
}


#endif //IMGUILAYER_H
