#include "Core/GeoXPCH.h"
#include "ImGuiLayer.h"
#include "Application.h"

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "imgui.h"
#include "3rdparty/imgui/examples/imgui_impl_opengl3.cpp"

// temporary
#include "GLFW/glfw3.h" 
//#include 

namespace GX{

ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"), m_Time(0.0f) {

}

ImGuiLayer::~ImGuiLayer() {}

void ImGuiLayer::OnAttach() {

    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    io.BackendPlatformName = "GeoX";

    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

    ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDetach() {}

void ImGuiLayer::OnUpdate() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::Get();

    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(),app.GetWindow().GetHeight());

    float time = (float)glfwGetTime();
    io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
    m_Time = time;
    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event &event){

    EventDispatcher dispatcher(event);
    
    dispatcher.Dispatch<WindowResizeEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));

    dispatcher.Dispatch<MouseButtonPressedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));

    dispatcher.Dispatch<KeyPressedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(GX_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));

}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[ (u_int16_t) event.GetMouseButton()] = true;
    return false;

}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
//    io.MouseReleased[ (u_int16_t) event.GetMouseButton()] = true;
    io.MouseDown[ (u_int16_t) event.GetMouseButton()] = false;
    return false;

}

bool ImGuiLayer::OnMouseButtonMovedEvent(MouseMovedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(event.GetX(), event.GetY());
    return false;

}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += event.GetXOffset();
    io.MouseWheel += event.GetYOffset();
    return false;

}

bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(event.GetWidth(),event.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.0f,1.0f);
    glViewport(0,0,event.GetWidth(),event.GetHeight());
    return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[(u_int16_t) event.GetKeyCode()] = true;

    io.KeyCtrl  = io.KeysDown[ GLFW_KEY_LEFT_CONTROL]   || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT]     || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt   = io.KeysDown[ GLFW_KEY_LEFT_ALT]       || io.KeysDown[ GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER]     || io.KeysDown[ GLFW_KEY_RIGHT_SUPER];

    return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[(u_int16_t) event.GetKeyCode()] = false;

    return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent &event){

    ImGuiIO& io = ImGui::GetIO();
    u_int16_t keycode = (u_int16_t) event.GetKeyCode();
    if(keycode>0 && keycode< 0x10000) io.AddInputCharacter((u_int16_t) keycode);
    return false;
}


}
