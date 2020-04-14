#include "Application.h"


extern GX::Application *GX::CreateApplication();

namespace GX
{
    Application* Application::s_Instance = nullptr;

    Application::Application() : 
        m_Running(true),
        m_Minimized(false),
        m_LastFrameTime(0.0f)
    {
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback( GX_BIND_EVENT_FN(Application::OnEvent) );
        m_LayerZero = new Layer();
        m_LayerImGui = new ImGuiLayer();
        m_LayerImGui->IsVisible() = false;
        PushLayer(m_LayerZero);
        PushOverlay(m_LayerImGui);

        // Temporary OpenGL binders

        // VERTEX BUFFER
        glGenVertexArrays(1,&m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[3*3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);

        // INDEX BUFFER (ELEMENT BUFFER)
        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
        
        u_int32_t indices[3] = {0, 1, 2};
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        std::string vertexSource = R"(

            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }

        )";

        std::string fragmentSource = R"(

            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main(){
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
            }
            
        )";

        m_Shader.reset(new Shader(vertexSource,fragmentSource));
    }

    Application::~Application() {}

    int Application::Main(){

        while(m_Running){

            glClearColor(0.11f,0.11f,0.10f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_Shader->Bind();
            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (auto* layer : m_LayerStack) if(layer->IsVisible()) layer->OnUpdate();

            m_LayerImGui->Begin();
            for (auto* layer : m_LayerStack) if(layer->IsVisible()) layer->OnImGuiRender();
            m_LayerImGui->End();

            m_Window->OnUpdate();
        }
        return 0;
    }

    void Application::PushLayer(Layer *layer){ 
        m_LayerStack.PushLayer(layer); 
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer){ 
        m_LayerStack.PushOverlay(layer); 
        layer->OnAttach();
    }

    void Application::OnEvent(Event &event){

        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(GX_BIND_EVENT_FN(Application::OnApplicationClose));

        for(auto aLayer = m_LayerStack.rbegin(); aLayer != m_LayerStack.rend(); aLayer++)
        if( (*aLayer)->IsVisible() ) {
            (*aLayer)->OnEvent(event);
            if(event.Handled) break;
        }

    }

    bool Application::OnApplicationClose(WindowCloseEvent &event){

        m_Running = false;
        return true;
    }

    void Application::SetArguments(int argc, char **argv) {
    
        for(int i=0; i<argc; i++) m_Argv.emplace_back(argv[i]);

    }

}

int main(int argc, char **argv)
{

    GX::Logger::Init();
    LOG_CORE_INFO("You are playing with GeoX. Be nice with it.");

    auto app = GX::CreateApplication();
    app->SetArguments(argc,argv);
    auto exitCode = app->Main();
    delete app;

    return exitCode;
}
