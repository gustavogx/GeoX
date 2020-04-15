#include "Core/Core.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGLContext.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace GX{
    
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle){

    }

    void OpenGLContext::Init(){
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        GX_CORE_ASSERT(status,"Failed to Initialize GLAD");

        LOG_CORE_INFO("OpenGL Renderer: {0}, {1}, {2}", glGetString(GL_VENDOR), glGetString(GL_VERSION), glGetString(GL_RENDERER));

    }

    void OpenGLContext::SwapBuffers(){
        glfwSwapBuffers(m_WindowHandle);
    }
}