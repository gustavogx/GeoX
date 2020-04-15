#include "Core/Application.h"


extern GX::Application *GX::CreateApplication();

namespace GX
{
    Application* Application::s_Instance = nullptr;

    static GLenum ShaderDataTypetoOpenGLBaseType(ShaderDataType type){
        switch (type) {
            case GX::ShaderDataType::Float :    return GL_FLOAT;
            case GX::ShaderDataType::Float2 :   return GL_FLOAT;
            case GX::ShaderDataType::Float3 :   return GL_FLOAT;
            case GX::ShaderDataType::Float4 :   return GL_FLOAT;
            case GX::ShaderDataType::Mat3 :     return GL_FLOAT;
            case GX::ShaderDataType::Mat4 :     return GL_FLOAT;
            case GX::ShaderDataType::Int :      return GL_INT;
            case GX::ShaderDataType::Int2 :     return GL_INT;
            case GX::ShaderDataType::Int3 :     return GL_INT;
            case GX::ShaderDataType::Int4 :     return GL_INT;
            case GX::ShaderDataType::Bool :     return GL_BOOL;
        }
    }

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

        float vertices[3*7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_VertexBuffer.reset( VertexBuffer::Create(vertices, sizeof(vertices)) );

        {
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            };

            m_VertexBuffer->SetLayout(layout);
        }
        auto& layout = m_VertexBuffer->GetLayout();
        uint32_t index = 0;
        for(const auto& element : layout ){
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                element.GetElementCount(),
                ShaderDataTypetoOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*) (intptr_t) element.Offset );
            index++;
        }


        // INDEX BUFFER (ELEMENT BUFFER)
        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset( IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t) ) );

        std::string vertexSource = R"(

            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main(){
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }

        )";

        std::string fragmentSource = R"(

            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main(){
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
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
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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
