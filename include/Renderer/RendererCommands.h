#pragma once
#include "Core/Core.h"

#include "Renderer/RendererAPI.h"

namespace GX {

    class RenderCommand{
    public:

        inline static void SetClearColor(const glm::vec4& color){
            s_RendererAPI->SetClearColor(color);
        }

        inline static void Clear(){
            s_RendererAPI->Clear();
        }
        
        inline static void DrawIndexed(const RefPointer<VertexArray> &vertexArray){
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        
    private:
        static RendererAPI* s_RendererAPI;
    };
}