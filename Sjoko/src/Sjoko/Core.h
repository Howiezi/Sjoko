#pragma once

#ifdef SJ_PLATFORM_WINDOWS
  #ifdef SJ_BUILD_DLL
    #define SJOKO_API __declspec(dllexport)
  #else
    #define SJOKO_API __declspec(dllimport)
  #endif
#else
  #error Sjoko Engine only supports Windows!
#endif

#ifdef SJ_ENABLE_ASSERTS
  #define SJ_ASSERT(x, ...) {if(!(x)) {SJ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
  #define SJ_CORE_ASSERT(x, ...) {if(!(x)) {SJ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
  #define SJ_ASSERT(x, ...)
  #define SJ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)