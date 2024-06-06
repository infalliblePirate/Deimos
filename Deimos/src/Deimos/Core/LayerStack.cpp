#include "LayerStack.h"
#include "dmpch.h"

// LayerStack is like a wrapper for a vector of layers
namespace Deimos {
    LayerStack::LayerStack() {
    }

    LayerStack::~LayerStack() {
        for (Layer *layer: m_layers){
            layer->onDetach();
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer *layer) {
        m_layers.emplace(m_layers.begin() + m_layerInsertIndex,
                         layer); // m_layerInst is only updated for layers to enable layer insertion in the middle
        layer->onAttach();
        m_layerInsertIndex++;
    }

    void LayerStack::pushOverlay(Layer *overlay) {
        m_layers.push_back(overlay); // overlays must be at the back of the stack
        overlay->onAttach();
    }

    void LayerStack::popLayer(Layer *layer) {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, layer); // range: [first, last)
        if (it != m_layers.begin() + m_layerInsertIndex) {
            // if the element was not found - returns last
            layer->onDetach();
            m_layers.erase(it);
            --m_layerInsertIndex;
        }
    }

    void LayerStack::popOverlay(Layer *overlay) {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_layerInsertIndex, overlay);
        if (it != m_layers.end())
            overlay->onDetach();
            m_layers.erase(it);
    }
}
