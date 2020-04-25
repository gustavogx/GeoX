#pragma once
#include "Core/Core.h"

#include "Renderer/Buffers.h"

namespace GX{

    class VertexArray {
    public:
        virtual ~VertexArray() {}
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const RefPointer<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const RefPointer<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<RefPointer<VertexBuffer>>& GetVertexBuffer() const = 0;
        virtual const RefPointer<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();

    };

}
