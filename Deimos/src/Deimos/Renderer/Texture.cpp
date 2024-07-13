#include "Texture.h"
#include "stb_image/stb_image.h"

#include <memory>

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Deimos {

    Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height) {
        switch(Renderer::getAPI()) {
            case RendererAPI::API::None: DM_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(width, height);
        }
        DM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref <Texture2D> Texture2D::create(const std::string &path) {
        switch(Renderer::getAPI()) {
            case RendererAPI::API::None: DM_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }
        DM_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}