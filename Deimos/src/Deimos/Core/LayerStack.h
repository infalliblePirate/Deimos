#ifndef ENGINE_LAYERSTACK_H
#define ENGINE_LAYERSTACK_H

#include "Core.h"
#include "Layer.h"
#include <vector>

namespace Deimos
{
    class DM_API LayerStack {
    public:
        LayerStack();
        ~LayerStack();

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* overlay);
        void popLayer(Layer* layer);
        void popOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_layers.begin(); } // to be able to use foreach
        std::vector<Layer*>::iterator end() { return m_layers.end(); }

    private:
        std::vector<Layer*> m_layers;
        unsigned int m_layerInsertIndex = 0;

    };

}


#endif //ENGINE_LAYERSTACK_H
