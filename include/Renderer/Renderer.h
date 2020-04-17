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

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}