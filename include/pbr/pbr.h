#ifndef INCLUDE_PBR_H_
#define INCLUDE_PBR_H_

#if defined(_WIN32)
  #ifdef PBR_SHARED_LIB_EXPORT
    #define PBR_API __declspec(dllexport)
  #else
    #define PBR_API __declspec(dllimport)
  #endif
#elif defined(__GNUC__) || defined(__clang__)
  #ifdef PBR_SHARED_LIB_EXPORT
    #define PBR_API __attribute__((visibility("default")))
  #else
    #define PBR_API
  #endif
#else
  #define PBR_API
#endif

#include <engine.h>

#endif
