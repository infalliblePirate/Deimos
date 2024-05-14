#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include "glm/glm/glm.hpp"

namespace Deimos {

    class Shader {
    public:
        virtual ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static Shader* create(const std::string& vertexSrc, const std::string& fragmentSrc);
    };
}


#endif //ENGINE_SHADER_H
