#pragma once
#include "Core/Core.h"

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace GX{

    class OpenGLContext : public GraphicsContext{
    private:
        GLFWwindow* m_WindowHandle;
    public:

        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    };

}