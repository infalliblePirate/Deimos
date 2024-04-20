#include "Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Deimos/Renderer/Renderer.h"

namespace Deimos {

    VertexBuffer *VertexBuffer::create(float* vertices, uint32_t size) {
        switch (Renderer::getAPI()) {
            case RendererAPI::None: DM_ASSERT(false, "Deimos currently does not support RendererAPI::None!");
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        DM_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    IndexBuffer *IndexBuffer::create(uint32_t* indices, int count) {
        switch (Renderer::getAPI()) {
            case RendererAPI::None: DM_ASSERT(false, "Deimos currently does not support RendererAPI::None!");
            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
        }
        DM_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
