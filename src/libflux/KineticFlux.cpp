#include "libflux/Flux.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D Kinetic::compute(Array2D const& LSol, Array2D const& RSol) {
      auto const [hL,qL] = LSol;
      auto const [hR,qR] = RSol;

      // Fast return on dry zones
      if (hL < heps && hR < heps) return {0.,0.};

      auto uL = qL / hL;
      auto uR = qR / hR;
      auto TL = halfGrav * hL;
      auto TR = halfGrav * hR;
      auto sqrt_3_TL = std::sqrt(3. * TL);
      auto sqrt_3_TR = std::sqrt(3. * TR);
      auto maxP = std::max(0., uL + sqrt_3_TL);
      auto maxM = std::max(0., uL - sqrt_3_TL);
      auto minP = std::min(0., uR + sqrt_3_TR);
      auto minM = std::min(0., uR - sqrt_3_TR);

      Array2D fluxP = {0.5*(std::pow(maxP,2) - std::pow(maxM,2)), (std::pow(maxP,3) - std::pow(maxM,3))/3};
      Array2D fluxM = {0.5*(std::pow(minP,2) - std::pow(minM,2)), (std::pow(minP,3) - std::pow(minM,3))/3};
      fluxP *= hL / (2. * sqrt_3_TL);
      fluxM *= hR / (2. * sqrt_3_TR);

      return fluxP + fluxM;
    }

  } // namespace Flux

} // namespace SWES1D
