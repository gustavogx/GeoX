#include "Application.h"


extern GX::Application *GX::CreateApplication();

namespace GX
{
    Application* Application::s_Instance = nullptr;

    Application::Application(){
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback( GX_BIND_EVENT_FN(Application::OnEvent) );
        PushLayer(new ImGuiLayer());
    }

    Application::~Application() {}

    int Application::Main(){

        while(m_Running){

            glClearColor(0.11f,0.11f,0.10f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (auto* layer : m_LayerStack) layer->OnUpdate();

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

        for(auto aLayer = m_LayerStack.rbegin(); aLayer != m_LayerStack.rend(); aLayer++){
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
