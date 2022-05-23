#ifndef SWES1D_SOLVER_HPP
#define SWES1D_SOLVER_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "libmodel/Model.hpp"
#include "libflux/Flux.hpp"
#include "TimeScheme.hpp"
#include "libboundaryconditions/BoundaryConditions.hpp"

namespace SWES1D
{

  template<typename ModelType, typename FluxType, typename TimeSchemeType,
           typename LeftBCType, typename RightBCType>
  class Solver {
  private:
    Parameters* params_;

  public:
    explicit Solver(Parameters* params): params_(params) {}

    void solve() {
      ModelType model;
      TimeSchemeType timeScheme(params_->dt);
      LeftBCType leftBC;
      RightBCType rightBC;

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
      Vector<Array2D> U(params_->nx, {1., 0.});

      while (time < params_->tf) {
        buildRHS(rhs);
        U = timeScheme.computeOneTimeStep(U, time, rhs);
        time += params_->dt;
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
