#pragma once
#include "Core/Core.h"

#include "Renderer/RendererCommands.h"
#include "Renderer/Shader.h"
#include "Renderer/Cameras.h"
#include "glm/glm.hpp"

namespace GX{

    class Renderer{
    private:
        struct ScreenData{
            glm::mat4 ViewProjectionMatrix;
        };

        static ScreenData* m_ScreenData;

    public:

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const RefPointer<Shader>& shader, const RefPointer<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}