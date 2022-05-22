add_library(libsolver
  Solver.cpp)

target_link_libraries(libsolver PUBLIC
  libtypes
  libparameters
  libmodel
  libflux
  libtimescheme
  libboundaryconditions)
