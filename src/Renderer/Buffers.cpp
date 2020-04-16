#include "Core/Core.h"
#include "Core/Core.h"
#include "Renderer/Buffers.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace GX{

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: GX_CORE_ASSERT(false, "RendererAPI::API:: None is currently not supported.")
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }

        GX_CORE_ASSERT(false, "Unknown RendererAPI.")
        return nullptr;
    };

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: GX_ASSERT(false, "RendererAPI::API:: None is currently not supported.")
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }

        GX_CORE_ASSERT(false, "Unknown RendererAPI.")
        return nullptr;
    };
    
}