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
    explicit Solver(Parameters* params):
      params_(params) {};

    void solve() {

      struct RHSFunc {
        Vector<Array2D> operator()(Real time, Vector<Array2D> const& U) {
          Vector<Array2D> rhs;
          return U;
        }
      };

      RHSFunc rhs;
      Vector<Array2D> U(100, {1., 0.5});
      Real time = 1.;
      TimeSchemeType timeScheme(params_->dt);
      U = timeScheme.computeOneTimeStep(U, time, rhs);
    }

  };

} // namespace SWES1D

#endif // SWES1D_SOLVER_HPP
