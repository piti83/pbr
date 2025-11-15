file(GLOB pbr-example-sphere "examples/sphere/sphere.cc")
add_executable(sphere ${pbr-example-sphere})
target_link_libraries(sphere PRIVATE pbr_shared_lib)
