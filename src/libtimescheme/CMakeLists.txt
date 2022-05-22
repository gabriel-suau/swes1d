add_library(libtimescheme
  Euler.cpp
  Heun.cpp)

target_link_libraries(libtimescheme PUBLIC libtypes)
