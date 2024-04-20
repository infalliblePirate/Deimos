#ifndef ENGINE_OPENGLBUFFER_H
#define ENGINE_OPENGLBUFFER_H

#include "Deimos/Renderer/Buffer.h"

namespace Deimos {

    class OpenGLVertexBuffer : public VertexBuffer{
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer() override;

        virtual void bind() const override;
        virtual void unbind() const override;
    private:
        uint32_t m_rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer{
    public:
        OpenGLIndexBuffer(uint32_t* indices, int counter);
        virtual ~OpenGLIndexBuffer() override;

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual int getCount() const override;
    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };


}


#endif //ENGINE_OPENGLBUFFER_H
