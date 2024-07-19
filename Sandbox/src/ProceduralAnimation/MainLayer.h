#pragma once

#include "Deimos.h"
#include "Deimos/Core/Layer.h"

class MainLayer : public Deimos::Layer {
public:
    MainLayer();
    virtual ~MainLayer() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Deimos::Timestep timestep) override;
    virtual void onEvent(Deimos::Event &event) override;

    virtual void onImGuiRender() override;
private:
    bool onMouseMovedEvent(Deimos::MouseMovedEvent &e);
private:
    Deimos::OrthographicCameraController m_cameraController;
    glm::vec3 m_circlePos{0.f};
};