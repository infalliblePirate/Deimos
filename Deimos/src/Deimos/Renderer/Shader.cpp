#include "dmpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Deimos {
    Shader* Shader::create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None: DM_ASSERT(false, "Deimos currently does not support RendererAPI::None!");
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
        }
        DM_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}