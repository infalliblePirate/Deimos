#include "MainLayer.h"
#include "Deimos/Events/MouseEvent.h"
#include "Deimos/Core/Core.h"

using namespace Deimos;

MainLayer::MainLayer() : m_cameraController(1280 / 720.f) {

}

void MainLayer::onAttach() {
    DM_PROFILE_FUNCTION();

    Deimos::Renderer2D::init();
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
        Renderer2D::drawCircle(m_circlePos, 0.1f, 6, { 107.f / 255, 142.f / 255, 35.f / 255, 1.f });
        Renderer2D::drawCircle({ 1280 / 720.f, 0.f, 0.3 }, 0.1f, 6, { 92.f / 255, 60.f / 255, 35.f / 255, 1.f });
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

bool MainLayer::onMouseMovedEvent(MouseMovedEvent &e) {
    auto& window = Application::get().getWindow();
    std::cout << "E.GETX()" << e.getX() << std::endl;
    std::cout << "2.f * e.getx() / window.getWidth() - 1:" << (2.f * e.getX() / window.getWidth()) - 1.f << std::endl;
    // convert to camera coordinates: x from -window.getWidth() / window.getHeight() to window.getWidth() / window.getHeight()
    m_circlePos = { ((2.f * e.getX() / window.getWidth()) - 1.f) * window.getWidth() / window.getHeight(), 1.f  - (2.f * e.getY() / window.getHeight()), 0.f};
    return false;
}
