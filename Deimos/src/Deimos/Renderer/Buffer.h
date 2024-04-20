#ifndef ENGINE_BUFFER_H
#define ENGINE_BUFFER_H


namespace Deimos {

    class VertexBuffer {
    public:
        virtual ~VertexBuffer(){};

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer(){};

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        static IndexBuffer* create(uint32_t* indices, int count);
        virtual int getCount() const = 0;
    };
}


#endif //ENGINE_BUFFER_H
