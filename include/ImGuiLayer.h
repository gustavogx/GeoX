#pragma once
#include "Core/Core.h"
#include "Layer.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace GX{

class ImGuiLayer : public Layer{

private:
    float m_Time;

public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;

    void OnEvent(Event &event) override;

private:

    bool OnWindowResizeEvent(WindowResizeEvent &event);

    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);
    bool OnMouseButtonMovedEvent(MouseMovedEvent &event);
    bool OnMouseScrolledEvent(MouseScrolledEvent &event);

    bool OnKeyPressedEvent(KeyPressedEvent &event);    
    bool OnKeyReleasedEvent(KeyReleasedEvent &event);    
    bool OnKeyTypedEvent(KeyTypedEvent &event);    
    
};

}
