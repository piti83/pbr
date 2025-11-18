add_library(pbr_shared_lib SHARED
  ${pbr-src}
)

target_compile_definitions(pbr_shared_lib PRIVATE PBR_SHARED_LIB_EXPORT)

set_target_properties(pbr_shared_lib PROPERTIES PUBLIC_HEADER include/pbr/pbr.h)

target_include_directories(pbr_shared_lib PUBLIC include)
target_include_directories(pbr_shared_lib PUBLIC src)

target_link_libraries(pbr_shared_lib PUBLIC
  glfw
  Vulkan::Vulkan
  spdlog
)
