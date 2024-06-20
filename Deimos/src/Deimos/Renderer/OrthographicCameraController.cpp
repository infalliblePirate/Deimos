#include "dmpch.h"
#include "OrthographicCameraController.h"

#include "Deimos/Core/Input.h"
#include "Deimos/Core/KeyCodes.h"
#include "Deimos/Core/Application.h"

namespace Deimos {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
            : m_aspectRatio(aspectRatio), m_rotation(rotation),
              m_camera(-aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel) {

    }

    void OrthographicCameraController::onUpdate(Deimos::Timestep ts) {
        DM_PROFILE_FUNCTION();

        if (Deimos::Input::isKeyPressed(DM_KEY_LEFT)) {
            m_cameraPosition.x -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
            m_cameraPosition.y -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
        } else if (Deimos::Input::isKeyPressed(DM_KEY_RIGHT)) {
            m_cameraPosition.x += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
            m_cameraPosition.y += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
        }

        if (Deimos::Input::isKeyPressed(DM_KEY_UP)) {
            m_cameraPosition.x -= sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
            m_cameraPosition.y += cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
        } else if (Deimos::Input::isKeyPressed(DM_KEY_DOWN)) {
            m_cameraPosition.x += sin(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
            m_cameraPosition.y -= cos(glm::radians(m_cameraRotation)) * m_cameraTranslationSpeed * ts;
        }

        if (m_rotation) {
            if (Deimos::Input::isKeyPressed(DM_KEY_A)) {
                m_cameraRotation += m_cameraRotationSpeed * ts;
            } else if (Deimos::Input::isKeyPressed(DM_KEY_D)) {
                m_cameraRotation -= m_cameraRotationSpeed * ts;
            }

            if(m_cameraRotation > 180.f) m_cameraRotation -= 360.f; // from -pi to pi
            else if (m_cameraRotation < -180.f) m_cameraRotation += 360.f;
            m_camera.setRotation(m_cameraRotation);
        }

        m_camera.setPosition(m_cameraPosition);
        m_cameraTranslationSpeed = m_zoomLevel * 0.25f;
    }

    void OrthographicCameraController::onEvent(Event &e) {
        DM_PROFILE_FUNCTION();

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent & e) {
        DM_PROFILE_FUNCTION();

        m_zoomLevel -= e.getYOffset() * 0.25f;
        m_zoomLevel = std::max(m_zoomLevel, 0.25f);
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent &e) {
        DM_PROFILE_FUNCTION();
        
        m_aspectRatio = (float) e.getWidth() / (float) e.getHeight();
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

}
