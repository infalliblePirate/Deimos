#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Deimos {
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
            : m_viewMatrix(1.f) {
        DM_PROFILE_FUNCTION();

        m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f); // scene parallelepiped
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::recalculateViewMatrix() {
        DM_PROFILE_FUNCTION();

        glm::mat4 transform = glm::translate(glm::mat4(1.f), m_position);
        transform = glm::rotate(transform, glm::radians(m_rotation), glm::vec3(0, 0, 1));

        m_viewMatrix = glm::inverse(transform);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::setProjection(float left, float right, float bottom, float top) {
        DM_PROFILE_FUNCTION();

        m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.f, 1.f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}
