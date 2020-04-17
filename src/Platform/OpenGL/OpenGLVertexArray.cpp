

#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "glad/glad.h"

namespace GX{

    static GLenum ShaderDataTypetoOpenGLBaseType(ShaderDataType type){
        switch (type) {
            case GX::ShaderDataType::Float :    return GL_FLOAT;
            case GX::ShaderDataType::Float2 :   return GL_FLOAT;
            case GX::ShaderDataType::Float3 :   return GL_FLOAT;
            case GX::ShaderDataType::Float4 :   return GL_FLOAT;
            case GX::ShaderDataType::Mat3 :     return GL_FLOAT;
            case GX::ShaderDataType::Mat4 :     return GL_FLOAT;
            case GX::ShaderDataType::Int :      return GL_INT;
            case GX::ShaderDataType::Int2 :     return GL_INT;
            case GX::ShaderDataType::Int3 :     return GL_INT;
            case GX::ShaderDataType::Int4 :     return GL_INT;
            case GX::ShaderDataType::Bool :     return GL_BOOL;
        }
    }

    OpenGLVertexArray::OpenGLVertexArray(){
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray(){
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
//        GX_CORE_ASSERT(vertexBuffer->GetLayout(), "Vertex Buffer has no layout.")

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();


        uint32_t index = 0;
        auto& layout = vertexBuffer->GetLayout();
        for(const auto& element : layout ){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                element.GetElementCount(),
                ShaderDataTypetoOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*) (intptr_t) element.Offset );
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();
        m_IndexBuffer = indexBuffer;
        
    }

}