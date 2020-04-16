#include "Core/Core.h"
#include "Renderer/RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GX {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}