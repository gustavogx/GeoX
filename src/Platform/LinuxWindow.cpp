#include "Platform/LinuxWindow.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Renderer/GraphicsContext.h"

#include "glad/glad.h"


namespace GX{

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description){
        LOG_CORE_ERROR("GLFW Error ({0}): {1}",error,description);
    }

    Window* Window::Create(const WindowProperties &propeties){

        return new LinuxWindow(propeties);

    }

    LinuxWindow::LinuxWindow(const WindowProperties &propeties){

        Init(propeties);

    }

    LinuxWindow::~LinuxWindow(){

        Shutdown();

    }

    void LinuxWindow::Init(const WindowProperties &propeties){
        m_Data.Title = propeties.Title;
        m_Data.Width = propeties.Width;
        m_Data.Height = propeties.Height;

        if(!s_GLFWInitialized){

            int success = glfwInit();
            glfwSetErrorCallback(GLFWErrorCallback);
            assert(success);
            s_GLFWInitialized = true;

        }

        m_Window = glfwCreateWindow(m_Data.Width,m_Data.Height,m_Data.Title.c_str(),nullptr,nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        // Bind to GLFW callbacks

        //OnResize
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            data.Height = height;
            data.Width = width;

            WindowResizeEvent event(width,height);
            data.EventCallback(event);
        });

        //OnClose
        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        //OnKeyPressed, OnKeyReleased, OnKeyRepeat
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			data.EventCallback(event);
		});

        //OnMouseClick, OnMouseRelease
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.EventCallback(event);
					break;
				}
			}
		});

        //OnMouseScroll
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

        //OnMouseMove
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

    }

    void LinuxWindow::OnUpdate(){
        glfwPollEvents();
		m_Context->SwapBuffers();

    }

    void LinuxWindow::SetVSync(const bool &enabled){

        if(enabled) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        m_Data.VSync = enabled;

    }

    void LinuxWindow::Shutdown(){

        glfwDestroyWindow(m_Window);

    }

}