/**
 * \file IOManager.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Definition of the IO routines
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

#ifndef SWES1D_IOMANAGER_HPP
#define SWES1D_IOMANAGER_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "Topography.hpp"

#include <fstream>

namespace SWES1D
{

  struct IOManager {
    static void saveParameters(Parameters const& params,
                        std::string const& filename) {
      std::ofstream file(filename);
    }

    template<typename TopographyType>
    static void saveTopography(Parameters const& params,
                        TopographyType const& topo,
                        std::string const& filename) {
      std::ofstream file(filename);
      auto const xmin = params.xmin;
      auto const dx = params.dx;

      file << "#  x     z" << std::endl;
      for (int i = 0 ; i < params.nx ; i++) {
        auto const x = xmin + (i + 0.5) * dx;
        file << x << " " << topo.z[i] << std::endl;
      }

    }

    template<typename TopographyType>
    static void saveSol(Parameters const& params,
                 TopographyType const& topo,
                 Vector<Array2D> const& U,
                 std::string const& filename) {
      std::ofstream file(filename);
      auto const xmin = params.xmin;
      auto const dx = params.dx;

      file << "#  x     h     h+z     q     u" << std::endl;
      for (int i = 0 ; i < params.nx ; i++) {
        auto const x = xmin + (i + 0.5) * dx;
        auto const [h,q] = U[i];
        file << x << " " << h << " " << h+topo.z[i] << " " << q << " " << ((h == 0) ? 0. : q / h) << std::endl;
      }

    }
  };

} // namespace SWES1D

#endif // SWES1D_IOMANAGER_HPP
