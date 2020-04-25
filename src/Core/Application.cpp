
#include "Core/Application.h"

#include "Renderer/Renderer.h"
#include "Renderer/RendererCommands.h"

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
        m_Window = ScopePointer<Window>(Window::Create());
        m_Window->SetVSync(true);
        m_Window->SetEventCallback( GX_BIND_EVENT_FN(Application::OnEvent) );
        m_LayerZero = new Layer();
        m_LayerImGui = new ImGuiLayer();
        m_LayerImGui->IsVisible() = false;
        PushLayer(m_LayerZero);
        PushOverlay(m_LayerImGui);

    }

    Application::~Application() {}

    int Application::Main(){

        while(m_Running){

            float time = GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

            for (auto* layer : m_LayerStack) if(layer->IsVisible()) layer->OnUpdate(timestep);

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
