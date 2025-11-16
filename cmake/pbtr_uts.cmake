add_executable(pbr_uts
  ${pbr-uts}
)

target_link_libraries(pbr_uts PRIVATE
  pbr_shared_lib
  gtest
  gtest_main
)

add_test(NAME pbr_uts COMMAND pbr_uts)
