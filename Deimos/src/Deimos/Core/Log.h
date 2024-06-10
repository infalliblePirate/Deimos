#ifndef ENGINE_LOG_H
#define ENGINE_LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h" // MUST BE INCLUDED to support logging custom data

namespace Deimos {
    class DM_API Log {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger> & getCoreLogger(){
            return s_coreLogger;
        }
        inline static std::shared_ptr<spdlog::logger> & getClientLogger(){
            return s_clientLogger;
        }
    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
}

#ifdef DEBUG_BUILD
// Core log macros
#define DM_CORE_TRACE(...) Deimos::Log::getCoreLogger()->trace(__VA_ARGS__)
#define DM_CORE_INFO(...) Deimos::Log::getCoreLogger()->info(__VA_ARGS__)
#define DM_CORE_WARN(...) Deimos::Log::getCoreLogger()->warn(__VA_ARGS__)
#define DM_CORE_ERROR(...) Deimos::Log::getCoreLogger()->error(__VA_ARGS__)
#define DM_CORE_CRITICAL(...) Deimos::Log::getCoreLogger()->critical(__VA_ARGS__)

// Cleint log macros
#define DM_TRACE(...) Deimos::Log::getClientLogger()->trace(__VA_ARGS__)
#define DM_INFO(...) Deimos::Log::getClientLogger()->info(__VA_ARGS__)
#define DM_WARN(...) Deimos::Log::getClientLogger()->warn(__VA_ARGS__)
#define DM_ERROR(...) Deimos::Log::getClientLogger()->error(__VA_ARGS__)
#define DM_CRITICAL(...) Deimos::Log::getClientLogger()->critical(__VA_ARGS__)
#else
// Define empty macros for release builds
#define DM_CORE_TRACE(...)
#define DM_CORE_INFO(...)
#define DM_CORE_WARN(...)
#define DM_CORE_ERROR(...)
#define DM_CORE_CRITICAL(...)

#define DM_TRACE(...)
#define DM_INFO(...)
#define DM_WARN(...)
#define DM_ERROR(...)
#define DM_CRITICAL(...)
#endif // DEBUG_BUILD

#endif //ENGINE_LOG_H
