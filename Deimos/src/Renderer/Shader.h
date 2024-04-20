#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>

namespace Deimos {

    class Shader {
    public:
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();

        void bind() const;
        void unbind() const;
    private:
        uint32_t m_rendererID;
    };
}


#endif //ENGINE_SHADER_H
