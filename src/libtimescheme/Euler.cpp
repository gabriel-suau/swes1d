#include "libtimescheme/TimeScheme.hpp"

namespace SWES1D
{

  template<RHSConcept RHSFunc>
  Vector<Array2D>& Euler::computeOneTimeStep(Vector<Array2D>& U,
                                             Real time,
                                             RHSFunc rhs) {
    U += dt_ * rhs(time, U);
    return U;
  }

} // namespace SWES1D
