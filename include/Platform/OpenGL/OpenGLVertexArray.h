#pragma once
#include "Core/Core.h"

#include "Renderer/VertexArray.h"

namespace GX {

    class OpenGLVertexArray : public VertexArray {
    private:
        std::vector<RefPointer<VertexBuffer>> m_VertexBuffers;
        RefPointer<IndexBuffer> m_IndexBuffer;
        uint32_t m_RendererID;

    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const RefPointer<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const RefPointer<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<RefPointer<VertexBuffer>>& GetVertexBuffer() const override {return m_VertexBuffers;}
        virtual const RefPointer<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;}

    };

}