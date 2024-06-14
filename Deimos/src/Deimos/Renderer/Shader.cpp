#include "dmpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Deimos {

    Ref<Shader> Shader::create(const std::string &filepath) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:    DM_ASSERT(false, "Deimos currently does not support RendererAPI::None!");
            case RendererAPI::API::OpenGL:  return createRef<OpenGLShader>(filepath);
        }
        DM_ASSERT(false, "Unknown RendererAPI!");
    }

    Ref<Shader> Shader::create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        switch (Renderer::getAPI()) {
            case RendererAPI::API::None:    DM_ASSERT(false, "Deimos currently does not support RendererAPI::None!");
            case RendererAPI::API::OpenGL:  return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }
        DM_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }


    ////////////////////////////////// library ///////////////////////////////////////////

    void ShaderLibrary::add(const std::string& name, const Ref<Shader> &shader) {
        DM_CORE_ASSERT(!exists(shader->getName()), "Shader already exists!");
        m_shaders[shader->getName()] = shader;
    }

    void ShaderLibrary::add(const Ref<Shader> &shader) {
        add(shader->getName(), shader);
    }

    Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string &filepath) {
        auto shader = Shader::create(filepath);
        add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::load(const std::string &filepath) {
        auto shader = Shader::create(filepath);
        add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::get(const std::string &name) {
        DM_CORE_ASSERT(exists(name), "Shader not found!");
        return m_shaders[name];
    }

    bool ShaderLibrary::exists(const std::string &name) const {
        return m_shaders.find(name) != m_shaders.end();
    }
}