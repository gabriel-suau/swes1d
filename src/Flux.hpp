/**
 * \file Flux.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Definition of the numerical fluxes
 *
 * \copyright SWES1D : Monodimensional Shallow Water Equations Solvers
 * Copyright (C) 2022 Gabriel Suau
 *
 * \copyright This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * \copyright This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * \copyright You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SWES1D_FLUX_HPP
#define SWES1D_FLUX_HPP

#include "Types.hpp"

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


    struct Rusanov {
      static Array2D compute(Array2D const& LSol, Array2D const& RSol) {
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

    };


    struct HLL {
      static Array2D compute(Array2D const& LSol, Array2D const& RSol) {
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

    };


    struct HLLE {
      static Array2D compute(Array2D const& LSol, Array2D const& RSol) {
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
    };

    struct Kinetic {
      static Array2D compute(Array2D const& LSol, Array2D const& RSol) {
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
    }; // struct Kinetic

  } // namespace Flux

} // namespace SWES1D

#endif // SWES1D_FLUX_HPP
