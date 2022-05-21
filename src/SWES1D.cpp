#include "SWES1D.hpp"
#include <iostream>

using namespace SWES1D;

int main(int argc, char** argv)
{

  NumericalFlux<Rusanov> flux;

  Array2D LSol = {0.5, 1.2};
  Array2D RSol = {1.4, 0.4};

  auto res = flux.compute(LSol, RSol);

  std::cout << res[0] << " " << res[1] / res[0] << std::endl;

  return EXIT_SUCCESS;

}
