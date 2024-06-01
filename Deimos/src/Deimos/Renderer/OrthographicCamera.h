#ifndef ENGINE_ORTHOGRAPHICCAMERA_H
#define ENGINE_ORTHOGRAPHICCAMERA_H

#include <glm/glm/glm.hpp>

namespace Deimos {
    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        const glm::vec3& getPosition() const { return m_position; }
        void setPosition(const glm::vec3& position) { m_position = position; recalculateViewMatrix(); }

        float getRotation() const { return m_rotation; }
        void setRotation(float rotation) { m_rotation = rotation; recalculateViewMatrix(); }

        const glm::mat4& getProjectionMatrix() const { return m_viewProjectionMatrix; }
        const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

        void setProjection(float left, float right, float bottom, float top);
    private:
        void recalculateViewMatrix();
    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position = {0.f, 0.f, 0.f};
        float m_rotation = 0.0f;
    };
}


#endif //ENGINE_ORTHOGRAPHICCAMERA_H
