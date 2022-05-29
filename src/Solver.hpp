#ifndef SWES1D_SOLVER_HPP
#define SWES1D_SOLVER_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "libmodel/Model.hpp"
#include "Topography.hpp"
#include "Flux.hpp"
#include "TimeScheme.hpp"
#include "libboundaryconditions/BoundaryConditions.hpp"

namespace SWES1D
{

  template<typename ModelType, typename TopographyType, typename FluxType,
           typename TimeSchemeType, typename LeftBCType, typename RightBCType>
  class Solver {
  private:
    Parameters* params;

  public:
    explicit Solver(Parameters* params): params(params) {}

    void solve() {
      ModelType model;
      TopographyType topo;
      LeftBCType leftBC;
      RightBCType rightBC;

      /** Setup the topography */
      topo.setup(*params);

      // This is what is passed as the RHS to the time scheme method
      // It has to be built using the model, the topography, the
      // numerical flux and the boundary conditions
      struct RHSType {
        Vector<Array2D> operator()(Real time, Vector<Array2D> const& U) {
          Vector<Array2D> rhs;
          return U;
        }
      };
      RHSType rhs;

      Real time = 0.;
      int iter = 0;

      // Initial solution
      Vector<Array2D> U(10, {1., 0.});

      while (time < params->tf) {
        buildRHS(rhs);
        U = TimeSchemeType::computeOneTimeStep(U, time, params->dt, rhs);
        time += params->dt;
        iter++;
      }

    } // Solver::solve

  private:
    template<typename RHSType>
    RHSType& buildRHS(RHSType& rhs) {
      return rhs;
    }
  };

} // namespace SWES1D

#endif // SWES1D_SOLVER_HPP
