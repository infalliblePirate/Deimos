#include "dmpch.h"
#include "OrthographicCameraController.h"

#include "Deimos/Input.h"
#include "Deimos/KeyCodes.h"
#include "Application.h"

namespace Deimos {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
            : m_aspectRatio(aspectRatio), m_rotation(rotation), m_camera(-aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel) {

    }

    void OrthographicCameraController::onUpdate(Deimos::Timestep ts) {
        if (Deimos::Input::isKeyPressed(DM_KEY_LEFT)) {
            m_cameraPosition.x -= m_cameraTranslationSpeed * ts;
        } else if (Deimos::Input::isKeyPressed(DM_KEY_RIGHT)) {
            m_cameraPosition.x += m_cameraTranslationSpeed * ts;
        }

        if (Deimos::Input::isKeyPressed(DM_KEY_UP)) {
            m_cameraPosition.y += m_cameraTranslationSpeed * ts;
        } else if (Deimos::Input::isKeyPressed(DM_KEY_DOWN)) {
            m_cameraPosition.y -= m_cameraTranslationSpeed * ts;
        }

        if (m_rotation) {
            if (Deimos::Input::isKeyPressed(DM_KEY_A)) {
                m_cameraRotation += m_cameraRotationSpeed * ts;
            } else if (Deimos::Input::isKeyPressed(DM_KEY_D)) {
                m_cameraRotation -= m_cameraRotationSpeed * ts;
            }
            m_camera.setRotation(m_cameraRotation);
        }

        m_camera.setPosition(m_cameraPosition);
        m_cameraTranslationSpeed = m_zoomLevel;
    }

    void OrthographicCameraController::onEvent(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<MouseScrolledEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
        dispatcher.dispatch<WindowResizeEvent>(DM_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
    }

    bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent &e) {
        m_zoomLevel -= e.getYOffset() * 0.25f;
        m_zoomLevel = std::max(m_zoomLevel, 0.25f);
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

    bool OrthographicCameraController::onWindowResized(WindowResizeEvent &e) {
        m_aspectRatio = (float)e.getWidth()/(float)e.getHeight();
        m_camera.setProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

}
