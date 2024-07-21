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

        for (size_t i = 0; i < m_numJoints; ++i) {
            Renderer2D::drawCircle(m_spineJoints[i].position, m_spineJoints[i].radius, 32, m_bodyColor);
        }
        
        Renderer2D::drawLine({0.8f, 0.5f, 0.5f}, {1.f, -2.f, 0.5}, 5.2f, {1.f, 1.f, 1.f, 1.f});
        Renderer2D::drawLine({-1.f, 0.5f, 0.5f}, {0.6f, 2.f, 0.5}, 5.2f, {1.f, 1.f, 1.f, 1.f});

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

void MainLayer::updateJointsPos()
{
    m_spineJoints[0].position = m_headPos;
    for (size_t i = 1; i < m_numJoints; ++i) {
        m_spineJoints[i].position = attachToBody(m_spineJoints[i - 1].position, m_spineJoints[i].position, m_startDistance + (i * 0.002));
    }
}

glm::vec3 MainLayer::attachToBody(glm::vec3 &achnor, glm::vec3 &point, float distance) {
    return glm::normalize(point - achnor) * distance + achnor; // obtain normalized vector * distance and translate it to anchor position
}

bool MainLayer::onMouseMovedEvent(MouseMovedEvent &e) {
    auto& window = Application::get().getWindow();
    // convert to camera coordinates: x from -window.getWidth() / window.getHeight() to window.getWidth() / window.getHeight(), y from -1 to 1
    m_headPos = { ((2.f * e.getX() / window.getWidth()) - 1.f) * window.getWidth() / window.getHeight(), 1.f  - (2.f * e.getY() / window.getHeight()), 0.f};        
    updateJointsPos(); // recalculate position 

    return false;
}
