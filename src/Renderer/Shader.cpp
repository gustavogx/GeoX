#include "Core/Core.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

#ifdef GX_PLATFORM_LINUX
    #include "Platform/OpenGL/OpenGLShader.h"
#endif

namespace GX{

    Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: GX_ASSERT(false, "RendererAPI:: None is currently not supported.")
            case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSource, fragmentSource);
        }

        GX_CORE_ASSERT(false, "Unknown RendererAPI.")
        return nullptr;
    };



}
