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

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
        virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;
    private:
        uint32_t m_rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };
}


#endif //ENGINE_OPENGLVERTEXARRAY_H
