#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererCommand.h"

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

        m_VertexArray.reset( VertexArray::Create() );

        float vertices[3*7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        m_VertexBuffer.reset( VertexBuffer::Create(vertices, sizeof(vertices)) );

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        uint32_t indices[3] = {0, 1, 2};
        m_IndexBuffer.reset( IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t) ) );
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_SquareVA.reset( VertexArray::Create() );

        float squareVertices[3*4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f
        };

        std::shared_ptr<VertexBuffer> squareVB;
        squareVB.reset( VertexBuffer::Create(squareVertices,sizeof(squareVertices)) );

        squareVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
        });

        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<IndexBuffer> squareIB;
        squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices)/sizeof(uint32_t) ) );

        m_SquareVA->SetIndexBuffer(squareIB);

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
                color = v_Color;
            }
            
        )";

        m_Shader.reset(new Shader(vertexSource,fragmentSource));

        std::string blueShaderVertexSource = R"(

            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main(){
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }

        )";

        std::string blueShaderFragmentSource = R"(

            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main(){
                color = vec4(0.1f, 0.1f, 0.9f, 1.0f);
            }
            
        )";        

        m_BlueShader.reset(new Shader(blueShaderVertexSource,blueShaderFragmentSource));
    }

    Application::~Application() {}

    int Application::Main(){

        while(m_Running){

            RenderCommand::SetClearColor({ 0.11f,0.11f,0.10f,1.0f } );
            RenderCommand::Clear();

            Renderer::BeginScene();
            
                m_BlueShader->Bind();
                Renderer::Submit(m_SquareVA); 
                
                m_Shader->Bind();
                m_VertexArray->Bind();
                Renderer::Submit(m_VertexArray); 
            
            Renderer::EndScene();

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