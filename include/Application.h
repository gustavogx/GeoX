#pragma once
#include "Core/Core.h"
#include "Platform/LinuxWindow.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"

int main(int argc, char **argv);


namespace GX
{

class Application
{
private:
    std::vector<std::string> m_Argv;
    
    bool m_Running = true;
    bool m_Minimized = false;
    LayerStack m_LayerStack;
    //ImGuiLayer* m_ImGuiLayer;

    std::unique_ptr<Window> m_Window;

    float m_LastFrameTime = 0.0f;

    static Application * s_Instance;

public:

    Application();
    virtual ~Application();

    int Main();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window& GetWindow() { return *m_Window; }
    inline static Application& Get() { return *s_Instance; }

    void SetArguments(int argc, char **argv);
    inline u_int8_t GetArgc() const { return m_Argv.size(); }
    inline std::vector<std::string>& GetArgv(const int &index) { return m_Argv; }

    //Events
    void OnEvent(Event &event); 

private:

    bool OnApplicationClose(WindowCloseEvent &event);

private:
    friend int ::main(int argc, char **argv);
};

Application* CreateApplication(); // Defined at Client side with GX_APPLICATION() macro.
#define GX_APPLICATION(ClientApp) GX::Application* GX::CreateApplication(){ return new ClientApp(); }

} // namespace GX
