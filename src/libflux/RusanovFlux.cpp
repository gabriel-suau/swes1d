#include "libflux/Flux.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D Rusanov::compute(Array2D const& LSol, Array2D const& RSol) {
      auto const [hL,qL] = LSol;
      auto const [hR,qR] = RSol;

      // Fast return on dry zones
      if (hL < heps && hR < heps) return {0.,0.};

      auto uL = qL / hL;
      auto uR = qR / hR;

      auto c = std::max(std::abs(uL) + std::sqrt(grav * hL),
                        std::abs(uR) + std::sqrt(grav * hR));

      return (0.5 * (phyFlux(hR,uR) + phyFlux(hL,uL) - c * (RSol - LSol)));
    }

  } // namespace Flux

} // namespace SWES1D
