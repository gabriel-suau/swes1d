add_library(libflux
  PhyFlux.cpp
  RusanovFlux.cpp
  HLLFlux.cpp
  HLLEFlux.cpp
  KineticFlux.cpp)

target_link_libraries(libflux PUBLIC libtypes)
