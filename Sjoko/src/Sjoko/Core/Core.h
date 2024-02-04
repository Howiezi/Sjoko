#pragma once

#include <memory>

#ifdef _WIN32
  #ifdef _WIN64
    #define SJ_PLATFORM_WINDOWS
  #else
    #error "x86 Builds are not supported!"
  #endif
#elif defined(__APPLE__) || defined(__MACH__)
  #include <TargetConditionals.h>
  // Must check all platforms because TARGET_OS_MAC exists on all of them
  #if TARGET_IPHONE_SIMULATOR == 1
    #error "IOS simulator is not supported!"
  #elif TARGET_OS_IPHONE == 1
    #define SJ_PLATFORM_IOS
    #error "IOS is not supported!"
  #elif TARGET_OS_MAC == 1
    #define SJ_PLATFORM_MACOS
    #error "MacOS is not supported!"
  #else
    #error "Unknown Apple Platform!"
  #endif
// Android before linux, because andoird is based on linux kernel
#elif defined(__ANDROID__)
  #define SJ_PLATFORM_ANDROID
  #error "Android is not supported!"
#elif defined(__linux__)
  #define SJ_PLATFORM_LINUX
  #error "Linux is not supported!"
#else
  #error "Unknown platform!"
#endif
// DLL support
#ifdef SJ_PLATFORM_WINDOWS
  #if SJ_DYNAMIC_LINK
    #ifdef SJ_BUILD_DLL
      #define SJOKO_API __declspec(dllexport)
    #else
      #define SJOKO_API __declspec(dllimport)
    #endif
  #else
    #define SJOKO_API
  #endif
#else
  #error Sjoko Engine only supports Windows!
#endif // End of DLL support

#ifdef SJ_DEBUG
  #define SJ_ENABLE_ASSERTS
#endif

#ifdef SJ_ENABLE_ASSERTS
  #define SJ_ASSERT(x, ...) {if(!(x)) {SJ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define SJ_CORE_ASSERT(x, ...) {if(!(x)) {SJ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define SJ_ASSERT(x, ...)
  #define SJ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SJ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Sjoko {

  template<typename T>
  using Scope = std::unique_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Scope<T> CreateScope(Args&& ... args)
  {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  using Ref = std::shared_ptr<T>;
  template<typename T, typename ... Args>
  constexpr Ref<T> CreateRef(Args&& ... args)
  {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

}