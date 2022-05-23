#ifndef SWES1D_TOPOGRAPHY_HPP
#define SWES1D_TOPOGRAPHY_HPP

#include "Types.hpp"
#include "Parameters.hpp"

namespace SWES1D
{

  namespace Topography
  {

    template<typename TopographyType>
    struct Topography {
      Vector<Real> z;
      Vector<Real> grav_dz;

      Topography& setup(Parameters const& params) {
        this->buildTopo(params).buildGravDz(params);
        return *this;
      }

    protected:
      Topography& buildTopo(Parameters const& params) {
        return static_cast<TopographyType*>(this)->buildTopo(params);
      }

      Topography& buildGravDz(Parameters const& params) {
        auto nx = params.nx;
        auto dx = params.dx;
        auto gravInvTwoDx = grav / (2 * dx);

        assert(this->z.size() == nx);

        this->grav_dz.resize(nx);

        // Compute the derivative of the topography using a second order
        // centered finite difference formula
        this->grav_dz[0] = - gravInvTwoDx * (- 3 * this->z[0] + 4 * this->z[1] - this->z[2]);
        for (int i = 1 ; i < nx - 1 ; i++) {
          this->grav_dz[i] = - gravInvTwoDx * (this->z[i+1] - this->z[i-1]);
        }
        this->grav_dz[nx-1] = - gravInvTwoDx * (- 3 * this->z[nx-1] + 4 * this->z[nx-2] - this->z[nx-1]);
        
        return *this;
      }

    }; // template struct Topography

    template<typename TopoFuncType>
    struct Generated: public Topography<Generated<TopoFuncType>> {

      Generated& buildTopo(Parameters const& params) {
        TopoFuncType topoFunc;
        auto xmin = params.xmin;
        auto nx = params.nx;
        auto dx = params.dx;
        this->z.resize(nx);
        // Generate the actual topography
        for (int i = 0 ; i < nx ; i++) {
          Real x = xmin + (i + 0.5) * dx;
          this->z[i] = topoFunc(x);
        }
        return *this;
      }

    }; // struct Generated

    // struct Measured: public Topography<Measured> {
    //   Measured& buildTopo(Parameters const& params) {
    //     return *this;
    //   }
    // }; // struct Measured

    // struct XZArray: public Topography<XZArray> {
    //   XZArray& buildTopo(Parameters const& params) {
    //     return *this;
    //   }
    // }; // struct XZArray

  } // namespace Topography

} // namespace SWES1D

#endif // SWES1D_TOPOGRAPHY_HPP
