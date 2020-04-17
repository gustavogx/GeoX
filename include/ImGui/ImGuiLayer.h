#pragma once

#include "Core/Layer.h"
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

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnImGuiRender() override;
    
    void Begin();
    void End();

};

}
