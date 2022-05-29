add_executable(bump_fluvial main.cpp)
target_include_directories(bump_fluvial PUBLIC ${swes1d_source_dir})
target_link_libraries(bump_fluvial PRIVATE ${swes1d_lib_name})
add_test(NAME bump_fluvial
  COMMAND "./bump_fluvial")
