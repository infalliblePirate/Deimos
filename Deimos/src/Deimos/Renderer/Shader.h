#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include "glm/glm/glm.hpp"

namespace Deimos {

    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;

        void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    private:
        uint32_t m_rendererID;
    };
}


#endif //ENGINE_SHADER_H
