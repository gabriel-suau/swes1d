add_library(libflux
  PhyFlux.cpp
  RusanovFlux.cpp
  HLLFlux.cpp
  KineticFlux.cpp)

target_link_libraries(libflux PUBLIC libtypes)
