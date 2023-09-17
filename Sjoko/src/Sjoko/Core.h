#pragma once

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
#endif

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