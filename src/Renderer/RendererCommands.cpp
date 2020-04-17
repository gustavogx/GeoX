

#include "Renderer/RendererCommands.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GX {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}