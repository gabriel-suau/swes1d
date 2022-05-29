#ifndef SWES1D_INITIALIZATION_HPP
#define SWES1D_INITIALIZATION_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "Topography.hpp"

namespace SWES1D
{

  namespace InitialCondition
  {

    template<typename InitFuncType>
    struct Generated {
      template<typename TopographyType>
      static void setup(Parameters const& params,
                        TopographyType const& topo,
                        Vector<Array2D>& sol) {
        InitFuncType initFunc;
        auto const xmin = params.xmin;
        auto const nx = params.nx;
        auto const dx = params.dx;
        sol.resize(nx);
        for (int i = 0 ; i < nx ; i++) {
          auto const x = xmin + (i + 0.5) * dx;
          sol[i] = initFunc(x);
          sol[i][0] -= topo.z[i];
        }
      }
    };

  } // namespace Initialization

} // namespace SWES1D

#endif // SWES1D_INITIALIZATION_HPP
