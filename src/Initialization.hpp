/**
 * \file Initialization.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Setup the initial condition
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

#ifndef SWES1D_INITIALIZATION_HPP
#define SWES1D_INITIALIZATION_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "Topography.hpp"

namespace SWES1D
{

  namespace InitialCondition
  {

    template<typename InitFuncType>
    struct Generated {
      template<typename TopographyType>
      static void setup(Parameters const& params,
                        TopographyType const& topo,
                        Vector<Array2D>& sol) {
        InitFuncType initFunc;
        auto const xmin = params.xmin;
        auto const nx = params.nx;
        auto const dx = params.dx;
        sol.resize(nx);
        for (int i = 0 ; i < nx ; i++) {
          auto const x = xmin + (i + 0.5) * dx;
          sol[i] = initFunc(x);
          sol[i][0] -= topo.z[i];
        }
      }
    };

  } // namespace Initialization

} // namespace SWES1D

#endif // SWES1D_INITIALIZATION_HPP
