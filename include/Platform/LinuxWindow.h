#pragma once
#include "Core/GeoXPCH.h"
#include "Base/WindowBase.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace GX{

    class LinuxWindow : public Window {
    private:
        
        struct WindowData{
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFunction EventCallback;
        };

        WindowData m_Data;
        GLFWwindow *m_Window;



        virtual void Init(const WindowProperties &properties);
        virtual void Shutdown();

    public:
        LinuxWindow(const WindowProperties &properties);
        virtual ~LinuxWindow();

        void OnUpdate() override;
        inline virtual void* GetNativeWindow() const override {return m_Window; }

        inline u_int16_t GetWidth() const override { return m_Data.Width; }
        inline u_int16_t GetHeight() const override { return m_Data.Height; }
        inline std::string GetTitle() const { return m_Data.Title; }

        inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(const bool &enabled);
        bool IsVSyncEnabled() const { return m_Data.VSync; }

    };

}