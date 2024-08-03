#ifndef ENGINE_OPENGLTEXTURE2D_H
#define ENGINE_OPENGLTEXTURE2D_H

#include "Deimos/Renderer/Texture.h"
#include <glad/glad.h>

namespace Deimos {
    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        virtual ~OpenGLTexture2D() override;

        virtual uint32_t getWidth() const override { return m_width; }
        virtual uint32_t getHeight() const override { return m_height; }

        virtual void bind(uint32_t slot = 0) const override;

        virtual void setData(void* data, uint32_t size) override;
    private:
        std::string m_path;

        uint32_t m_rendererID;
        uint32_t m_width;
        uint32_t m_height;

        GLenum m_internalFormat, m_dataFormat;
    };
}


#endif //ENGINE_OPENGLTEXTURE2D_H
