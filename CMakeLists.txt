cmake_minimum_required(VERSION 3.10)
project(SWES1D VERSION 1.0)
enable_language(CXX)

set(swes1d_source_dir ${PROJECT_SOURCE_DIR}/src)

##################################################
# SWES1D EXECUTABLE
##################################################
add_executable(SWES1D ${swes1d_source_dir}/SWES1D.cpp)
