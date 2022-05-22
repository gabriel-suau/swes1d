#ifndef SWES1D_SOLVER_HPP
#define SWES1D_SOLVER_HPP

#include "libtypes/Types.hpp"
#include "libparameters/Parameters.hpp"
#include "libmodel/Model.hpp"
#include "libflux/Flux.hpp"
#include "libtimescheme/TimeScheme.hpp"
#include "libboundaryconditions/BoundaryConditions.hpp"

namespace SWES1D
{

  template<Model::ModelConcept ModelType,
           Flux::FluxConcept FluxType,
           TimeScheme::TimeSchemeConcept TimeSchemeType,
           BC::BoundaryConditionConcept LeftBCType,
           BC::BoundaryConditionConcept RightBCType>
  class Solver {
  private:
    Parameters* params_;
  public:
    explicit Solver(Parameters* params):
      params_(params) {};
    void solve() { }
  };

} // namespace SWES1D

#endif // SWES1D_SOLVER_HPP
