#include "libflux/Flux.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D HLL::compute(Array2D const& LSol, Array2D const& RSol) {
      auto const [hL,qL] = LSol;
      auto const [hR,qR] = RSol;

      // Fast return on dry zones
      if (hL < heps && hR < heps) return {0.,0.};

      auto uL = qL / hL;
      auto uR = qR / hR;
      auto cL = std::sqrt(grav * hL);
      auto cR = std::sqrt(grav * hR);

      auto c1 = std::min(uL - cL, uR - cR);
      auto c2 = std::max(uL + cL, uR + cR);

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
