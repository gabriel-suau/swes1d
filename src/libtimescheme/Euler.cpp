#include "libtimescheme/TimeScheme.hpp"

namespace SWES1D
{

  namespace TimeScheme
  {

    template<typename RHSType>
    Vector<Array2D>& Euler::computeOneTimeStep(Vector<Array2D>& U,
                                               Real time,
                                               RHSType rhs) {
      U += dt_ * rhs(time, U);
      return U;
    }

  } // namespace TimeScheme

} // namespace SWES1D
