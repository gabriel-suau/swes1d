add_executable(bump_rest_immerged main.cpp)
target_include_directories(bump_rest_immerged PUBLIC ${swes1d_source_dir})
target_link_libraries(bump_rest_immerged PRIVATE ${swes1d_lib_name})
add_test(NAME bump_rest_immerged
  COMMAND "./bump_rest_immerged")
