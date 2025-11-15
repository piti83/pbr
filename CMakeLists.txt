cmake_minimum_required(VERSION 3.20)

project(pbr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
  add_compile_options(/FS)
endif()

include("cmake/libraries.cmake")

include("cmake/sources.cmake")

include("cmake/pbr_shared_lib.cmake")
include("cmake/pbtr_uts.cmake")
include("cmake/examples.cmake")
