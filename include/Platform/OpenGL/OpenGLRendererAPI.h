#pragma once
#include "Core/Core.h"

#include "Renderer/RendererAPI.h"

namespace GX{

    class OpenGLRendererAPI : public RendererAPI{
    public:

        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        virtual void DrawIndexed(const RefPointer<VertexArray>& vertexArray) override;

    };

}