#pragma once
#include "Core/Core.h"

#include "Renderer/Buffers.h"

namespace GX{

    class OpenGLVertexBuffer : public VertexBuffer{
    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer() override;
        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_Layout; }

    };

    class OpenGLIndexBuffer : public IndexBuffer{
    private:
        uint32_t m_RendererID;
        uint32_t m_Count;

    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual inline uint32_t GetCount() const override {return m_Count; }

    };    

}