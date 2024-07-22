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
    void updateJointsPosAndRotation();
    float calculateRotationAngle(const glm::vec3 &startVec, const glm::vec3 &endVec);
    glm::vec3 attachToBody(const glm::vec3& achnor, const glm::vec3& point, float distance);
    bool onMouseMovedEvent(Deimos::MouseMovedEvent &e);
private:
    Deimos::OrthographicCameraController m_cameraController;

    glm::vec4 m_bodyColor = { 95.f/255, 75.f/255, 180.f/255, 1.f };
    struct BodyPart {
        glm::vec3 pos{0.f};
        float radius;
        float rotation; // in radians
    };
    const static int m_numJoints = 10;

    glm::vec3 prevPos; // keep track of prev position to calculate how much every circle is rotated
    glm::vec3 m_headPos{0.f};
    glm::vec3 m_pointPos{1.f, 0.5f, 0.f};
    BodyPart m_spineJoints[m_numJoints]{};
    float m_connectingPoints[m_numJoints * 2]{}; // points that make up a body (x2 for both cides of a circle) 
    // *O*
    // *O*
    float m_startDistance = 0.1f;
};