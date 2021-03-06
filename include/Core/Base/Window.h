#pragma once
#include "Core/Core.h"

#include "Core/Base/Event.h"

namespace GX{

struct WindowProperties{
    std::string Title;
    u_int16_t Width;
    u_int16_t Height;

    WindowProperties(const std::string &title = "GeoX Application", const u_int16_t &w = 1280, const u_int16_t &h = 720) :
    Title(title), Width(w), Height(h) {}

};

struct WindowMouseChanges{
    float ScrollXOffset, ScrollYOffset, PositionXOffset, PositionYOffset;
private:
    float m_PreviousX, m_PreviousY;
};

class Window{
public:
    using EventCallbackFunction = std::function<void(Event&)>;

    virtual ~Window() {}

    virtual void OnUpdate() = 0;
    virtual u_int16_t GetWidth() const = 0;
    virtual u_int16_t GetHeight() const = 0;
    virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;

    static Window* Create(const WindowProperties& prop = WindowProperties());
    virtual void* GetNativeWindow() const = 0;

    virtual void SetVSync(const bool &enabled) = 0;
    virtual bool IsVSyncEnabled() const = 0;

    virtual WindowMouseChanges GetMouseChanges() const = 0;

};

}