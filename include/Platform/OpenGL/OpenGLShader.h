#pragma once
#include "Renderer/Shader.h"

namespace GX{

    class OpenGLShader :  public Shader{
    private:

        uint64_t m_RendererID;

    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformInt(const std::string& name, const int& value);

        void UploadUniformFloat(const std::string& name, const float& value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& values);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& values);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& values);

        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);


    };


}