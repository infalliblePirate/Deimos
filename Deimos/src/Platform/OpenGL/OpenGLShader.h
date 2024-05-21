#ifndef ENGINE_OPENGLSHADER_H
#define ENGINE_OPENGLSHADER_H

#include "Deimos/Renderer/Shader.h"
#include <glm/glm/glm.hpp>

namespace Deimos {
    class OpenGLShader : public Shader {
    public:
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
        virtual ~OpenGLShader();

        virtual void bind() const override;
        virtual void unbind() const override;

        void uploadUniformInt(const std::string& name, int value);

        void uploadUniformFloat(const std::string& name, float value);
        void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
        void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
    private:
        uint32_t m_rendererID;
    };
}


#endif //ENGINE_OPENGLSHADER_H
