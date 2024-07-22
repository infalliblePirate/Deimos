#include "MainLayer.h"
#include "Deimos/Events/MouseEvent.h"
#include "Deimos/Core/Core.h"

using namespace Deimos;

MainLayer::MainLayer() : m_cameraController(1280 / 720.f) {

}

void MainLayer::onAttach() {
    DM_PROFILE_FUNCTION();

    Deimos::Renderer2D::init();
    init();
}

void MainLayer::onDetach() {
    DM_PROFILE_FUNCTION();
}

void MainLayer::onUpdate(Timestep timestep) {
    DM_PROFILE_FUNCTION()

    {
        DM_PROFILE_SCOPE("CameraController::onUpdate");
        m_cameraController.onUpdate(timestep);
    }

    {
        DM_PROFILE_SCOPE("Renderer Prep");
        RenderCommand::setClearColor({0.7f, 0.7f, 0.8f, 1});
        RenderCommand::clear();
    }

    {
        DM_PROFILE_SCOPE("Renderer Draw");
        Renderer2D::beginScene(m_cameraController.getCamera());

        // starting positions for the upper and lower points
        glm::vec3 startPosUp = { m_spineJoints[0].pos.x + (m_spineJoints[0].radius * glm::cos((m_spineJoints[0].rotation) + M_PI / 6)), 
                                 m_spineJoints[0].pos.y + (m_spineJoints[0].radius * glm::sin((m_spineJoints[0].rotation) + M_PI / 6)), 0.8f };
        
        glm::vec3 startPosDown = { m_spineJoints[0].pos.x + (m_spineJoints[0].radius * glm::cos((m_spineJoints[0].rotation) - M_PI / 6)), 
                                   m_spineJoints[0].pos.y + (m_spineJoints[0].radius * glm::sin((m_spineJoints[0].rotation) - M_PI / 6)), 0.8f };

        Renderer2D::drawLine(startPosUp, startPosDown, 3.0f, m_bodyColor); // connect starting posistions
        glm::vec3 endPosUp = {};
        glm::vec3 endPosDown = {};
        // Renderer2D::drawCircle(startPosUp, 0.02f, 32, {0.f, 0.f, 0.f, 1.f});
        // Renderer2D::drawCircle(startPosDown, 0.02f, 32, {1.f, 1.f, 1.f, 1.f});

        for (size_t i = 0; i < m_numJoints; ++i) {
            //Renderer2D::drawCircle(m_spineJoints[i].pos, m_spineJoints[i].radius, 32, m_bodyColor);

            // calculate the new positions for the upper and lower points
            endPosUp = { m_spineJoints[i].pos.x + (m_spineJoints[i].radius * glm::cos((m_spineJoints[i].rotation) + M_PI / 2)), 
                                   m_spineJoints[i].pos.y + (m_spineJoints[i].radius * glm::sin((m_spineJoints[i].rotation) + M_PI / 2)), 0.8f };
            
            endPosDown = { m_spineJoints[i].pos.x + (m_spineJoints[i].radius * glm::cos((m_spineJoints[i].rotation) - M_PI / 2)), 
                                     m_spineJoints[i].pos.y + (m_spineJoints[i].radius * glm::sin((m_spineJoints[i].rotation) - M_PI / 2)), 0.8f };

            // draw circles at the new positions
            // Renderer2D::drawCircle(endPosUp, 0.02f, 32, {0.f, 0.f, 0.f, 1.f});
            // Renderer2D::drawCircle(endPosDown, 0.02f, 32, {1.f, 1.f, 1.f, 1.f});

            Renderer2D::drawLine(startPosUp, endPosUp, 3.0f, m_bodyColor);
            Renderer2D::drawLine(startPosDown, endPosDown, 3.0f, m_bodyColor);
            
            // update the start positions for the next iteration
            startPosUp = endPosUp;
            startPosDown = endPosDown;
        }
        Renderer2D::drawLine(endPosUp, endPosDown, 3.0f, m_bodyColor); // connect finishing posistions

        Renderer2D::endScene();
    }

}

void MainLayer::onEvent(Event &event) {
    m_cameraController.onEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.dispatch<MouseMovedEvent>(DM_BIND_EVENT_FN(MainLayer::onMouseMovedEvent));
}

void MainLayer::onImGuiRender() {

}

void MainLayer::init() {
    // Init the size of body parts
    m_spineJoints[0].radius = 0.1;
    m_spineJoints[1].radius = 0.12;
    m_spineJoints[2].radius = 0.13;
    m_spineJoints[3].radius = 0.122;
    m_spineJoints[4].radius = 0.113;
    m_spineJoints[5].radius = 0.09;
    m_spineJoints[6].radius = 0.075;
    m_spineJoints[7].radius = 0.055;
    m_spineJoints[8].radius = 0.047;
    m_spineJoints[9].radius = 0.027;
}

void MainLayer::updateJointsPosAndRotation() {
    m_spineJoints[0].rotation = calculateRotationAngle(glm::vec3(1, 0.f, 0.f), m_headPos - m_spineJoints[0].pos);
    m_spineJoints[0].pos = attachToBody(m_headPos, m_spineJoints[0].pos, m_startDistance);
    for (size_t i = 1; i < m_numJoints; ++i) {
        glm::vec3 prevPos = m_spineJoints[i].pos;
        m_spineJoints[i].pos = attachToBody(m_spineJoints[i - 1].pos, m_spineJoints[i].pos, m_startDistance + (i * 0.002));

        glm::vec3 vec = m_spineJoints[i].pos - prevPos;
        float rotationAngle = calculateRotationAngle(glm::vec3(1, 0.f, 0.f), vec); // angle between the positive direction of the Ox axis and the deviation vector
        m_spineJoints[i].rotation = rotationAngle;
    }
}

float MainLayer::calculateRotationAngle(const glm::vec3 &startVec, const glm::vec3 &endVec) {
    glm::vec3 normalizedStartVec = glm::normalize(startVec);
    glm::vec3 normalizedEndVec = glm::normalize(endVec);
    float dotProduct = glm::dot(normalizedStartVec, normalizedEndVec);
    float angle = glm::acos(dotProduct); // computes the smallest angle between 0 and pi

    glm::vec3 crossProduct = glm::cross(normalizedStartVec, normalizedEndVec);
    if (crossProduct.z < 0) { // determine the direction of rotation (if positive - counterclockwise, negative - clockwise)
        return -angle;
    }
    return angle;
}

glm::vec3 MainLayer::attachToBody(const glm::vec3 &achnor, const glm::vec3 &point, float distance) {
    return glm::normalize(point - achnor) * distance + achnor; // obtain normalized vector * distance and translate it to anchor position
}

bool MainLayer::onMouseMovedEvent(MouseMovedEvent &e) {
    auto& window = Application::get().getWindow();
    // convert to camera coordinates: x from -window.getWidth() / window.getHeight() to window.getWidth() / window.getHeight(), y from -1 to 1
    m_headPos = { ((2.f * e.getX() / window.getWidth()) - 1.f) * window.getWidth() / window.getHeight(), 1.f  - (2.f * e.getY() / window.getHeight()), 0.f};        
    updateJointsPosAndRotation(); // recalculate position and rotation 

    return false;
}
