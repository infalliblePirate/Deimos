#include "dmpch.h"
#include "OpenGLVertexArray.h"

#include <../vendor/GLAD/include/glad/glad.h>

namespace Deimos {

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:  return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:   return GL_FLOAT;
            case ShaderDataType::Mat4:   return GL_FLOAT;
            case ShaderDataType::Int:    return GL_INT;
            case ShaderDataType::Int2:   return GL_INT;
            case ShaderDataType::Int3:   return GL_INT;
            case ShaderDataType::Int4:   return GL_INT;
            case ShaderDataType::Bool:   return GL_BOOL;
        }

        DM_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        DM_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray() {
        DM_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_rendererID);
    }

    void OpenGLVertexArray::bind() const {
        DM_PROFILE_FUNCTION();

        glBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::unbind() const {
        DM_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer> &vertexBuffer) {
        DM_PROFILE_FUNCTION();

        DM_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_rendererID); // make sure the array is bound
        vertexBuffer->bind();

        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(m_VertexBufferIndex, element.getComponentCount(),
                                  ShaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  (const void*)(intptr_t)element.offset);
            m_VertexBufferIndex++;
        }
        m_vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer> &indexBuffer) {
        DM_PROFILE_FUNCTION();
        
        glBindVertexArray(m_rendererID);
        indexBuffer->bind();

        m_indexBuffer = indexBuffer;
    }

    const std::vector<Ref<VertexBuffer>> &OpenGLVertexArray::getVertexBuffers() const {
        return m_vertexBuffers;
    }

    const Ref<IndexBuffer> &OpenGLVertexArray::getIndexBuffer() const {
        return m_indexBuffer;
    }
}