#pragma once
#include "Core/Core.h"

#include "glm/glm.hpp"
#include "Renderer/VertexArray.h"

namespace GX{

    class RendererAPI{
    public:
        enum class API{
            None = 0,
            OpenGL =1 
        };

    private:

        static API s_API;

    public:

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;
        virtual void DrawIndexed(const RefPointer<VertexArray>& vertexArray) = 0;
        
        inline static RendererAPI::API GetAPI() { return s_API; }
    };
}