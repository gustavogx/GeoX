#pragma once

#include <string>

namespace GX{

    class Shader{
    private:

        u_int64_t m_RendererID;

    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind() const;
        void Unbind() const;

    };


}