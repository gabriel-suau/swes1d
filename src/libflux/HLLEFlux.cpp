#include "libflux/Flux.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D HLLE::compute(Array2D const& LSol, Array2D const& RSol) {
      auto const [hL,qL] = LSol;
      auto const [hR,qR] = RSol;

      // Fast return on dry zones
      if (hL < heps && hR < heps) return {0.,0.};

      auto uL = qL / hL;
      auto uR = qR / hR;
      auto cL = std::sqrt(grav * hL);
      auto cR = std::sqrt(grav * hR);

      auto uStar = 0.5 * (uL + uR) + cL - cR;
      auto hStar = std::pow(0.5 * (cL + cR) + 0.25  * (uL - uR), 2) / grav;
      auto cStar = std::sqrt(grav * hStar);

      Real c1, c2;
      if (hL < heps)
        c1 = uR - 2. * cR;
      else
        c1 = std::min(uL - cL, uStar - cStar);

      if (hR < heps)
        c2 = uL + 2. * cL;
      else
        c2 = std::max(uR + cR, uStar + cStar);

      if (std::abs(c1) < epsilon && std::abs(c2) < epsilon) {
        return {0.,0.};
      }
      else if (c1 >= epsilon) {
        return phyFlux(hL,uL);
      }
      else if (c2 <= -epsilon) {
        return phyFlux(hR,uR);
      }
      else {
        auto div = 1. / (c2 - c1);
        return ((c2 * phyFlux(hL,uL) - c1 * phyFlux(hR,uR) + c1 * c2 * (RSol - LSol)) * div);
      }
    }

  } // namespace Flux

} // namespace SWES1D
