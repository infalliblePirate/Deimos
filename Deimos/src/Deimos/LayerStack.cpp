#include "LayerStack.h"
#include "dmpch.h"

// LayerStack is like a wrapper for a vector of layers
namespace Deimos {

    LayerStack::LayerStack() {
        m_layerInsert = m_layers.begin(); // initializes iterator to point to the beginning of the m_layers
    }

    LayerStack::~LayerStack() {
        for (Layer *layer: m_layers)
            delete layer;
    }

    void LayerStack::pushLayer(Layer *layer) {
        m_layerInsert = m_layers.emplace(m_layerInsert,
                                         layer); // m_layerInst is only updated for layers to enable layer insertion in the middle
    }

    void LayerStack::pushOverlay(Layer *overlay) {
        m_layers.push_back(overlay); // overlays must be at the back of the stack
    }

    void LayerStack::popLayer(Layer *layer) {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer); // range: [first, last)
        if (it != m_layers.end()) { // if the element was not found - returns last
            m_layers.erase(it);
            --m_layerInsert;
        }
    }

    void LayerStack::popOverlay(Layer *overlay) {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
            m_layers.erase(it);
    }

}