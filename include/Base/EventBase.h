#pragma once
#include "Core/GeoXPCH.h"
#include "Core/Core.h"

namespace GX{

enum class EventType{

    None = 0,
    AppUpdate, AppRender, AppTick,
    WindowClose, WindowResize, WindowMoved, WindowGainedFocus, WindowLostFocus, 
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    KeyPressed, KeyReleased, KeyTyped

};

enum EventCategory{

    CategoryApplication = BIT(0),
    CategoryInput       = BIT(1),
    CategoryKeyboard    = BIT(2),
    CategoryMouse       = BIT(3),
    CategoryMouseButton = BIT(4)

};

#define EVENT_CLASS_TYPE(type) \
    static EventType GetStaticType() { return EventType::type; } \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


// Abstract Event Class
class Event
{
public:
    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & category;
    }
};

// Event Dispatcher
class EventDispatcher
{
private:
    Event& m_Event;

public:
    EventDispatcher(Event& event) : m_Event(event) {}
    
    template<typename T, typename F>
    bool Dispatch(const F& func)
    {
        if (m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.Handled = func(static_cast<T&>(m_Event));
            return true;
        }
        return false;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}


}