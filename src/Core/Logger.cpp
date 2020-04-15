#include "Core/Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace GX
{

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

void Logger::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    
    s_CoreLogger = spdlog::stdout_color_mt("GeoX");
    s_CoreLogger->set_level(spdlog::level::trace);
    
    s_ClientLogger = spdlog::stdout_color_mt("Client");
    s_ClientLogger->set_level(spdlog::level::trace);
}

} // namespace GX