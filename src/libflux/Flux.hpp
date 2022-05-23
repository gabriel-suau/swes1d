#ifndef SWES1D_FLUX_HPP
#define SWES1D_FLUX_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D phyFlux(Array2D Sol);
    Array2D phyFlux(Real h, Real u);
    // This allows to save one mult for the price of a comparison
    // Not sure if this is efficient...
    // Also requires #include <optional>
    // Array2D phyFlux(Real h, Real u, std::optional<Real> q = std::nullopt);

    // template<typename T>
    // concept FluxConcept = requires(T flux, Array2D const& uL, Array2D const& uR) {
    //   {flux.compute(uL, uR)} -> std::same_as<Array2D>;
    // };

    struct Rusanov {
      Array2D compute(Array2D const& LSol, Array2D const& RSol);
    };

    struct HLL {
      Array2D compute(Array2D const& LSol, Array2D const& RSol);
    };

    struct HLLE {
      Array2D compute(Array2D const& LSol, Array2D const& RSol);
    };

    struct Kinetic {
      Array2D compute(Array2D const& LSol, Array2D const& RSol);
    };

  } // namespace Flux

} // namespace SWES1D

#endif // SWES1D_FLUX_HPP
