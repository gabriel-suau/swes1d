#include "libtimescheme/TimeScheme.hpp"

namespace SWES1D
{

  namespace TimeScheme
  {

    template<RHSConcept RHSFunc>
    Vector<Array2D>& Heun::computeOneTimeStep(Vector<Array2D>& U,
                                              Real time,
                                              RHSFunc rhs) {
      auto k1 = rhs(time, U);
      auto k2 = rhs(time + dt_, U + dt_ * k1);
      U += dt_ * 0.5 * (k1 + k2);
      return U;
    }

  } // namespace TimeScheme

} // namespace SWES1D
