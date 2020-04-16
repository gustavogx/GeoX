#include "Renderer/VertexArray.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GX{

    VertexArray* VertexArray::Create(){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: GX_ASSERT(false, "RendererAPI:: None is currently not supported.")
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        GX_CORE_ASSERT(false, "Unknown RendererAPI.")
        return nullptr;
    };



}