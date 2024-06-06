#ifndef ENGINE_LAYER_H
#define ENGINE_LAYER_H

#include "Core.h"
#include "Deimos/Events/Event.h"
#include "Deimos/Core/Timestep.h"

namespace Deimos {
    class DM_API Layer {
    public:
        Layer(const std::string &debugName = "Layer");
        virtual ~Layer(); // so that derived classes' instances would be correctly deleted with this destructor invoked

        virtual void onAttach() {}; // add to LayerStack
        virtual void onDetach() {}; // remove from the LayerStack
        virtual void onUpdate(Deimos::Timestep timestep) {};
        virtual void onImGuiRender() {};
        virtual void onEvent(Event& event) {};

        inline const std::string& getName() const { return m_debugName; }
    protected:
        std::string m_debugName;
    };
}


#endif //ENGINE_LAYER_H
