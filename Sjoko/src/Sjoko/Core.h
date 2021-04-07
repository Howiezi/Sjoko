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