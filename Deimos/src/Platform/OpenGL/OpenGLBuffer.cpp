#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Deimos {

    ////////////////////////////////////////// Vertex Buffer ///////////////////////////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
        DM_PROFILE_FUNCTION();

        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);

        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        DM_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_rendererID);
    }

    void OpenGLVertexBuffer::bind() const {
        DM_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLVertexBuffer::unbind() const {
        DM_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    ////////////////////////////////////////// Index Buffer ////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, int count) : m_count(count){
        DM_PROFILE_FUNCTION();

        glGenBuffers(1, &m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        DM_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_rendererID);
    }

    void OpenGLIndexBuffer::bind() const {
        DM_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLIndexBuffer::unbind() const {
        DM_PROFILE_FUNCTION();
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    int OpenGLIndexBuffer::getCount() const {
        return m_count;
    }
}

