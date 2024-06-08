#ifndef ENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
#define ENGINE_ORTHOGRAPHICCAMERACONTROLLER_H

#include "Deimos/Renderer/OrthographicCamera.h"
#include "Deimos/Core/Timestep.h"

#include "Deimos/Events/ApplicationEvent.h"
#include "Deimos/Events/MouseEvent.h"


namespace Deimos {
    class OrthographicCameraController {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);
        void onUpdate(Timestep ts);
        void onEvent(Event& e);

        OrthographicCamera& getCamera() { return m_camera; }
        const OrthographicCamera& getCamera() const { return m_camera; }
    private:
        bool onMouseScrolled(MouseScrolledEvent& e);
        bool onWindowResized(WindowResizeEvent& e);
    private:
        float m_aspectRatio;
        float m_zoomLevel = 1.f;

        bool m_rotation;
        OrthographicCamera m_camera;

        glm::vec3 m_cameraPosition = { 0.f, 0.f, 0.f };
        float m_cameraRotation = 0.f;
        float m_cameraTranslationSpeed = 10, m_cameraRotationSpeed = 15.f;

    };
}


#endif //ENGINE_ORTHOGRAPHICCAMERACONTROLLER_H
