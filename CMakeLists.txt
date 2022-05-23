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
# LIBFLUX
##################################################
add_subdirectory(${swes1d_source_dir}/libflux)


##################################################
# LIBBOUNDARYCONDITIONS
##################################################
add_subdirectory(${swes1d_source_dir}/libboundaryconditions)


##################################################
# LIBSOLVER
##################################################
add_subdirectory(${swes1d_source_dir}/libsolver)


##################################################
# SWES1D LIBRARY
##################################################
add_library(${swes1d_lib_name} ${swes1d_source_dir}/dummy.cpp)
target_link_libraries(${swes1d_lib_name} PUBLIC
  libmodel
  libflux
  libboundaryconditions
  libsolver)

install(TARGETS ${swes1d_lib_name} LIBRARY)

##################################################
# BENCHMARKS
##################################################
# add_executable(${swes1d_exec_name} ${swes1d_source_dir}/SWES1D.cpp)
# target_link_libraries(${swes1d_exec_name} PUBLIC
#   libmodel
#   libflux
#   libboundaryconditions
#   libsolver)
