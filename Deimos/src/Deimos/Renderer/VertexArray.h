#ifndef ENGINE_VERTEXARRAY_H
#define ENGINE_VERTEXARRAY_H

#include "Deimos/Renderer/Buffer.h"
#include <memory>

namespace Deimos {
    class VertexArray {
    public:
        virtual ~VertexArray(){}

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        [[nodiscard]] virtual const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const = 0;
        [[nodiscard]] virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;

        static Ref<VertexArray> create();
    };
}



#endif //ENGINE_VERTEXARRAY_H
