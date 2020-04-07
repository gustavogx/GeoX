#pragma once

#include <memory>
#include "spdlog/spdlog.h"


namespace GX{

class Logger{
private:

    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;

public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() {return s_CoreLogger;}
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {return s_ClientLogger;}
};

}

#ifndef RELEASE

    #define LOG_CORE_TRACE(...) GX::Logger::GetCoreLogger()->trace(__VA_ARGS__)
    #define LOG_CORE_INFO(...) GX::Logger::GetCoreLogger()->info(__VA_ARGS__)
    #define LOG_CORE_WARN(...) GX::Logger::GetCoreLogger()->warn(__VA_ARGS__)
    #define LOG_CORE_ERROR(...) GX::Logger::GetCoreLogger()->error(__VA_ARGS__)
    #define LOG_CORE_FATAL(...) GX::Logger::GetCoreLogger()->fatal(__VA_ARGS__)
    #define LOG_CORE_CRITICAL(...) ::GX::Logger::GetCoreLogger()->critical(__VA_ARGS__)

    #define LOG_APP_TRACE(...) GX::Logger::GetClientLogger()->trace(__VA_ARGS__)
    #define LOG_APP_INFO(...) GX::Logger::GetClientLogger()->info(__VA_ARGS__)
    #define LOG_APP_WARN(...) GX::Logger::GetClientLogger()->warn(__VA_ARGS__)
    #define LOG_APP_ERROR(...) GX::Logger::GetClientLogger()->error(__VA_ARGS__)
    #define LOG_APP_FATAL(...) GX::Logger::GetClientLogger()->fatal(__VA_ARGS__)
    #define LOG_APP_CRITICAL(...) ::GX::Loggger::GetCoreLogger()->critical(__VA_ARGS__)

#else

    #define LOG_CORE_TRACE
    #define LOG_CORE_INFO
    #define LOG_CORE_WARN
    #define LOG_CORE_ERROR
    #define LOG_CORE_FATAL
    #define LOG_CORE_CRITICAL

    #define LOG_APP_TRACE
    #define LOG_APP_INFO
    #define LOG_APP_WARN
    #define LOG_APP_ERROR
    #define LOG_APP_FATAL
    #define LOG_APP_CRITICAL

#endif