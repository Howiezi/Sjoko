#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Sjoko {

  class SJOKO_API Log
  {
  public:
    static void Init();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };

}

// Core log macros
#define SJ_CORE_TRACE(...) ::Sjoko::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SJ_CORE_INFO(...) ::Sjoko::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SJ_CORE_WARN(...) ::Sjoko::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SJ_CORE_ERROR(...) ::Sjoko::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SJ_CORE_FATAL(...) ::Sjoko::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define SJ_TRACE(...) ::Sjoko::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SJ_INFO(...) ::Sjoko::Log::GetClientLogger()->info(__VA_ARGS__)
#define SJ_WARN(...) ::Sjoko::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SJ_ERROR(...) ::Sjoko::Log::GetClientLogger()->error(__VA_ARGS__)
#define SJ_FATAL(...) ::Sjoko::Log::GetClientLogger()->fatal(__VA_ARGS__)