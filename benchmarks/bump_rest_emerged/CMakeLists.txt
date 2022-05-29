add_executable(bump_rest_emerged main.cpp)
target_include_directories(bump_rest_emerged PUBLIC ${swes1d_source_dir})
target_link_libraries(bump_rest_emerged PRIVATE ${swes1d_lib_name})
add_test(NAME bump_rest_emerged
  COMMAND "./bump_rest_emerged")
