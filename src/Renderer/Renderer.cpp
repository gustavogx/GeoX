

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GX
{

Renderer::ScreenData* Renderer::m_ScreenData = new Renderer::ScreenData;

void Renderer::BeginScene(OrthographicCamera& camera)
{
    m_ScreenData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const RefPointer<Shader>& shader, const RefPointer<VertexArray> &vertexArray, const glm::mat4& transform)
{
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_ScreenData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

} // namespace GX