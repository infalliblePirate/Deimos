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
    void init();
    void updateJointsPos();
    glm::vec3 attachToBody(glm::vec3& achnor, glm::vec3& point, float distance);
    bool onMouseMovedEvent(Deimos::MouseMovedEvent &e);
private:
    Deimos::OrthographicCameraController m_cameraController;

    glm::vec4 m_bodyColor = {1/60.f, 1/120.f, 1/160.f, 1.f};
    struct BodyPart {
        glm::vec3 position;
        float radius;
    };
    const static int m_numJoints = 10;

    glm::vec3 m_headPos{0.f};
    glm::vec3 m_pointPos{1.f, 0.5f, 0.f};
    BodyPart m_spineJoints[m_numJoints]{};
    float m_startDistance = 0.1f;
};