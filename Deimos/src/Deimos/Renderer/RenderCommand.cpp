#include "dmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Deimos {
    Scope<RendererAPI> RenderCommand::s_rendererAPI = createScope<OpenGLRendererAPI>();
}