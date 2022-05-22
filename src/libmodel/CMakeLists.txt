add_library(libmodel
  FrictionModel.cpp
  InfiltrationModel.cpp
  RainModel.cpp)

target_link_libraries(libmodel PUBLIC libtypes)
