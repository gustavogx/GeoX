#pragma once
#include "Core/Core.h"

#include "glm/glm.hpp"

namespace GX{

    class Shader{
    private:

        uint64_t m_RendererID;

    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    };


}