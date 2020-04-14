#include "Core/GeoXPCH.h"
#include "Core/Core.h"
#include "Renderer/Buffers.h"
#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace GX{

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: GX_ASSERT(false, "RendererAPI:: None is currently not supported.")
            case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
    };

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size){

        switch (Renderer::GetAPI())
        {
            case RendererAPI::None: GX_ASSERT(false, "RendererAPI:: None is currently not supported.")
            case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }

    };
    
}