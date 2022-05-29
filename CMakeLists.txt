cmake_minimum_required(VERSION 3.10)
project(SWES1D VERSION 1.0)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 20)

set(swes1d_source_dir ${PROJECT_SOURCE_DIR}/src)
set(swes1d_lib_name ${PROJECT_NAME})

include_directories(${swes1d_source_dir})

##################################################
# LIBMODEL
##################################################
add_subdirectory(${swes1d_source_dir}/libmodel)


##################################################
# LIBBOUNDARYCONDITIONS
##################################################
add_subdirectory(${swes1d_source_dir}/libboundaryconditions)


##################################################
# SWES1D LIBRARY
##################################################
add_library(${swes1d_lib_name} ${swes1d_source_dir}/dummy.cpp)
target_link_libraries(${swes1d_lib_name} PUBLIC
  libmodel
  libboundaryconditions)

install(TARGETS ${swes1d_lib_name} LIBRARY)

##################################################
# BENCHMARKS
##################################################
option(SWES1D_ENABLE_BENCHMARKS "Build the SWES1D benchmark test suite" OFF)
include(CTest)

if (SWES1D_ENABLE_BENCHMARKS)

  set(swes1d_bench_dir ${PROJECT_SOURCE_DIR}/benchmarks)

  # add_subdirectory(${swes1d_bench_dir}/bump_rest_immerged)
  # add_subdirectory(${swes1d_bench_dir}/bump_rest_emerged)
  add_subdirectory(${swes1d_bench_dir}/bump_fluvial)
  # add_subdirectory(${swes1d_bench_dir}/bump_transcritical)
  # add_subdirectory(${swes1d_bench_dir}/bump_transcritical_wshock)
  # add_subdirectory(${swes1d_bench_dir}/dam_break_wet)
  # add_subdirectory(${swes1d_bench_dir}/dam_break_dry)

endif(SWES1D_ENABLE_BENCHMARKS)
