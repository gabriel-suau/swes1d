/**
 * \file TimeScheme.hpp
 * \author Gabriel Suau <gabrielsuau2@gmail.com> (2022)
 * \version 1.0.0
 * \date 2022-05-29
 *
 * \brief Time integrators
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

#ifndef SWES1D_TIMESCHEME_HPP
#define SWES1D_TIMESCHEME_HPP

#include "Types.hpp"

namespace SWES1D
{

  namespace TimeScheme {

    template<typename TimeSchemeType>
    class TimeScheme {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        return TimeSchemeType::computeOneTimeStep(U, time, dt, rhs);
      }
    }; // template class TimeScheme

    class Euler: public TimeScheme<Euler> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        U += dt * rhs(time, U);
        return U;
      }
    }; // class Euler

    class Heun: public TimeScheme<Heun> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + dt, U + dt * k1);
        U += dt * 0.5 * (k1 + k2);
        return U;
      }
    }; // class Heun

    class MidPoint: public TimeScheme<MidPoint> {
    public:
      template<typename RHSType>
      static Vector<Array2D>& computeOneTimeStep(Vector<Array2D>& U,
                                                 Real time,
                                                 Real dt,
                                                 RHSType rhs) {
        auto k1 = rhs(time, U);
        auto k2 = rhs(time + 0.5 * dt, U + 0.5 * dt * k1);
        U += dt * k2;
        return U;
      }
    }; // class MidPoint

  } // namespace TimeScheme

} // namespace SWES1D

#endif // SWES1D_TIMESCHEME_HPP
