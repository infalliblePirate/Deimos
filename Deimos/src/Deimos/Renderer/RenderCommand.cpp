#include "dmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Deimos {
    RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}