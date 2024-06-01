#ifndef ENGINE_OPENGLVERTEXARRAY_H
#define ENGINE_OPENGLVERTEXARRAY_H

#include <vector>
#include "Deimos/Renderer/VertexArray.h"

namespace Deimos {
    class OpenGLVertexArray : public VertexArray{
    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;
        virtual const Ref<IndexBuffer>& getIndexBuffer() const override;
    private:
        uint32_t m_rendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };
}


#endif //ENGINE_OPENGLVERTEXARRAY_H
