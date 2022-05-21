#include "Flux.hpp"

namespace SWES1D
{

  namespace Flux
  {

    Array2D phyFlux(Array2D sol) {
      auto[h,q] = sol;
      return {q, q * q / h + 0.5 * grav * h * h};
    }

    Array2D phyFlux(Real h, Real u) {
      auto q = h * u;
      return {q, q * u + 0.5 * grav * h * h}; 
    }

    // Array2D phyFlux(Real h, Real u, std::optional<Real> q) {
    //   if (q != std::nullopt) {
    //     return {q.value(), q.value() * u + 0.5 * grav * h * h}; 
    //   }
    //   else {
    //     auto hu = h * u;
    //     return {hu, hu * u + 0.5 * grav * h * h}; 
    //   }
    // }

  } // namespace Flux

} // namespace SWES1D
