/**
 * \file Parameters.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Runtime parameters of the simulation
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

#ifndef SWES1D_PARAMETERS_HPP
#define SWES1D_PARAMETERS_HPP

#include "Types.hpp"

namespace SWES1D
{

  struct Parameters {

    Parameters():
      xmin(0.), xmax(1.), length(xmax-xmin), nx(100), dx(length/nx),
      tf(5.), dt(0.005), cfl(0.5),
      leftBC(BoundaryConditionChoice::ImpDischarge),
      rightBC(BoundaryConditionChoice::ImpWaterHeight),
      outputDir("output"), saveFreq(50)
    {}

    Parameters& setSpaceVariables(Real xmin, Real xmax, int nx) {
      this->xmin = xmin;
      this->xmax = xmax;
      this->nx = nx;
      this->length = xmax - xmin;
      this->dx = this->length / nx;
      return *this;
    }

    Parameters& setTimeVariables(Real tf, Real dt, Real cfl) {
      this->tf = tf;
      this->dt = dt;
      this->cfl = cfl;
      return *this;
    }

    Parameters& setBoundaryConditions(BoundaryConditionChoice leftBC,
                                      BoundaryConditionChoice rightBC) {
      this->leftBC = leftBC;
      this->rightBC = rightBC;
      return *this;
    }

    Parameters& setOutputParameters(std::string const& outputDir,
                             int saveFreq) {
      this->outputDir = outputDir;
      this->saveFreq = saveFreq;
      return *this;
    }

    void printParameters() {}

    /** Space variables */
    Real xmin;
    Real xmax;
    Real length;
    int nx;
    Real dx;

    /** Time variables */
    Real tf;
    Real dt;
    Real cfl;

    /** Boundary condition choices */
    BoundaryConditionChoice leftBC;
    BoundaryConditionChoice rightBC;

    /** Outputs */
    std::string outputDir;
    int saveFreq;

  }; // struct Parameters

} // namespace SWES1D

#endif // SWES1D_PARAMETERS_HPP
