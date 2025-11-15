#ifndef INCLUDE_PBR_H_
#define INCLUDE_PBR_H_

#ifdef _WIN32
  #ifdef PBR_SHARED_LIB_EXPORT
    #define PBR_API __declspec(dllexport)
  #else
    #define PBR_API __declspec(dllimport)
  #endif
#else
  #define PBR_API
#endif

#include <engine.h>

#endif
