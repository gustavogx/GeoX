#pragma once
#include "Core/Core.h"
#include "Platform/LinuxWindow.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffers.h"

int main(int argc, char **argv);


namespace GX
{

class Application
{
private:
    std::vector<std::string> m_Argv;
    
    bool m_Running;
    bool m_Minimized;
    float m_LastFrameTime;

    std::unique_ptr<Window> m_Window;

    Layer *m_LayerZero;
    ImGuiLayer *m_LayerImGui;
    
    LayerStack m_LayerStack;

    uint32_t m_VertexArray;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;

    static Application *s_Instance;

public:

    Application();
    virtual ~Application();

    int Main();

    void PushLayer(Layer *layer);
    void PushOverlay(Layer *layer);

    inline Window& GetWindow() { return *m_Window; }
    inline void RenderImGui(const bool &flag=true) { m_LayerImGui->IsVisible() = flag; }
    inline void RenderLayerZero(const bool &flag=true) { m_LayerZero->IsVisible() = flag; }
    inline static Application& Get() { return *s_Instance; }



    // Handling Entry Point 
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
