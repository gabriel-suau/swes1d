/**
 * \file Solver.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Resolution of the problem
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

#ifndef SWES1D_SOLVER_HPP
#define SWES1D_SOLVER_HPP

#include "Types.hpp"
#include "Parameters.hpp"
#include "Initialization.hpp"
#include "libmodel/Model.hpp"
#include "Topography.hpp"
#include "Flux.hpp"
#include "TimeScheme.hpp"
#include "libboundaryconditions/BoundaryConditions.hpp"
#include "IOManager.hpp"

namespace SWES1D
{

  template<typename ModelType, typename InitialConditionType,
           typename TopographyType, typename FluxType,
           typename TimeSchemeType, typename LeftBCType, typename RightBCType>
  class Solver {
  private:
    Parameters const* params;

  public:
    explicit Solver(Parameters const* params): params(params) {}

    void solve() {
      ModelType model;

      /** Save the parameters of the run */
      std::string filename = params->outputDir + "/parameters.txt";
      IOManager::saveParameters(*params, filename);

      /** Setup the topography */
      TopographyType topo;
      topo.setup(*params);

      /** Setup initial condition */
      Vector<Array2D> U;
      InitialConditionType::setup(*params, topo, U);

      /** Save the topography */
      filename = params->outputDir + "/topography.txt";
      IOManager::saveTopography(*params, topo, filename);

      /** Save the initial condition */
      filename = params->outputDir + "/solution_0.txt";
      IOManager::saveSol(*params, topo, U, filename);

      // This is what is passed as the RHS to the time scheme method
      // It has to be built using the model, the topography, the
      // numerical flux and the boundary conditions
      struct RHSType {
        Parameters const* params;
        TopographyType const* topo;
        Vector<Array2D> operator()(Real time, Vector<Array2D> const& U) {
          auto rhsArr = buildFluxContrib(*params, time, U);
          addTopoContrib(*params, U, *topo, rhsArr);
          return rhsArr;
        }
      };

      RHSType rhs{params, &topo};

      Real time = 0.;
      int iter = 0;

      while (time < params->tf) {
        U = TimeSchemeType::computeOneTimeStep(U, time, params->dt, rhs);
        time += params->dt;
        iter++;
          IOManager::saveSol(*params, topo, U, params->outputDir + "/solution_" + std::to_string(iter / params->saveFreq) + ".txt");
      }

    } // Solver::solve

  private:

    static Vector<Array2D> buildFluxContrib(Parameters const& params,
                                            Real t, Vector<Array2D> const& U) {
      auto nx = params.nx;
      Array2D LSol, RSol;
      Vector<Array2D> fluxVec(nx, {0.,0.});

      // LeftBC (Neumann only for now)
      fluxVec[0] += FluxType::compute(U[0], U[0]);

      // Interior edges
      for (std::size_t i = 0 ; i < nx - 1 ; i++) {
        auto flux = FluxType::compute(U[i], U[i+1]);
        fluxVec[i] -= flux;
        fluxVec[i+1] += flux;
      }

      // RightBC (Neumann only for now)
      fluxVec[nx-1] -= FluxType::compute(U[nx-1], U[nx-1]);

      // Divide by dx to get the contribution
      auto invDx =  1. / params.dx;

      return fluxVec * invDx;
    }

    static void addTopoContrib(Parameters const& params, Vector<Array2D> const& U,
                               TopographyType const& topo, Vector<Array2D>& rhs) {
      auto nx = params.nx;
      assert( nx == rhs.size() );
      for (int i = 0 ; i < nx ; i++) {
        rhs[i][1] -= topo.grav_dz[i] * U[i][0];
      }
    }

  };

} // namespace SWES1D

#endif // SWES1D_SOLVER_HPP
