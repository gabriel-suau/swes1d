#ifndef SWES1D_FLUX_HPP
#define SWES1D_FLUX_HPP

#include "libtypes/Types.hpp"

namespace SWES1D
{

  template<typename T>
  concept FluxType = requires(T flux, Array2D const& uL, Array2D const& uR) {
    flux.compute(uL, uR);
  };

  template<typename FluxType>
  struct NumericalFlux {
    Array2D compute(Array2D const& LSol, Array2D const& RSol) {
      return static_cast<FluxType*>(this)->compute(LSol, RSol);
    }
  };

  struct Rusanov: NumericalFlux<Rusanov> {
    Array2D compute(Array2D const& LSol, Array2D const& RSol);
  };

  struct HLL: NumericalFlux<HLL> {
    Array2D compute(Array2D const& LSol, Array2D const& RSol);
  };

  struct Kinetic: NumericalFlux<Kinetic> {
    Array2D compute(Array2D const& LSol, Array2D const& RSol);
  };

  Array2D phyFlux(Array2D Sol);
  Array2D phyFlux(Real h, Real u);

  // This allows to save one mult for the price of a comparison
  // Not sure if this is efficient...
  // Array2D phyFlux(Real h, Real u, std::optional<Real> q = std::nullopt);

} // namespace SWES1D

#endif // SWES1D_FLUX_HPP
